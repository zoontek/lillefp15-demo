"use strict";

const puppeteer = require("puppeteer");
const util = require("util");
const fs = require("fs");
const deburr = require("lodash.deburr");
const POOLS = require("./pools");

const BASE_URL = "https://www.paris.fr/equipements/piscines/tous-les-horaires";
const POOLS_MATCHING_TERMS = POOLS.map(pool => pool.id.split("-"));

const findPool = name => {
  const deburred = deburr(name).toLowerCase();
  const matchedIdx = POOLS_MATCHING_TERMS.findIndex(terms =>
    terms.every(term => deburred.includes(term))
  );
  return POOLS[matchedIdx];
};

const addDays = (ref, days) => {
  const date = new Date(ref.valueOf());
  date.setDate(date.getDate() + days);
  return date;
};

const writeFile = util.promisify(fs.writeFile);

const crawl = async () => {
  const browser = await puppeteer.launch({
    args: ["--no-sandbox"],
    headless: true
  });

  try {
    const page = await browser.newPage();
    await page.goto(BASE_URL);

    return await page.evaluate(() => {
      const elToText = el => el.textContent.trim();

      const mainTable = document.querySelector("main table");
      const poolTrs = [...mainTable.querySelectorAll("tbody tr")];

      const firstDay = elToText(
        mainTable.querySelector("thead th:nth-child(2)")
      );

      const pools = poolTrs.reduce((acc, tr) => {
        const name = elToText(tr.querySelector("td span"));
        const hourTds = [...tr.querySelectorAll("td:not(:first-child)")];

        const hours = hourTds.map(td => {
          const lineDivs = [...td.querySelectorAll("div")];
          return lineDivs.map(div => elToText(div.firstChild));
        });

        return [...acc, { name, hours }];
      }, []);

      return { firstDay, pools };
    });
  } catch (err) {
    throw err;
  } finally {
    await browser.close();
  }
};

crawl()
  .then(async data => {
    const [refDay, refMonth] = data.firstDay
      .replace(/[^0-9\/]/g, "")
      .split("/")
      .map(nbr => Number.parseInt(nbr));

    const refDate = new Date();

    refDate.setUTCDate(refDay);
    refDate.setUTCMonth(refMonth - 1);
    refDate.setUTCHours(12);
    refDate.setUTCMinutes(0);
    refDate.setUTCSeconds(0);
    refDate.setUTCMilliseconds(0);

    const [firstPool] = data.pools;

    const dates = firstPool.hours.map((_, idx) =>
      addDays(refDate, idx)
        .toJSON()
        .slice(0, 10)
    );

    const pools = data.pools
      .reduce((acc, { name, hours }) => {
        const pool = findPool(name);

        if (pool === undefined) {
          return acc;
        }

        const hoursMap = hours.map(dayHours => {
          return dayHours.reduce((acc, hour) => {
            const onlyHourChars = hour
              .replace(/[^0-9: ]/g, "")
              .replace(/[ ]{2,}/g, " ")
              .trim();

            if (onlyHourChars === "") {
              return acc;
            }

            return [...acc, onlyHourChars.split(" ")];
          }, []);
        });

        return [...acc, { ...pool, hours: hoursMap }];
      }, [])
      .sort((a, b) => a.name.localeCompare(b.name));

    return writeFile("./data.json", JSON.stringify({ dates, pools }));
  })
  .catch(err => {
    console.error(err);
  });

"use strict";

const http = require("http");
const fs = require("fs");

const PORT = 8080;
const DATA = fs.readFileSync("./data.json");

const sleep = delay =>
  new Promise(resolve => {
    setTimeout(resolve, delay);
  });

const server = http.createServer(async (_req, res) => {
  await sleep(1000);

  res.writeHead(200, { "Content-Type": "application/json" });
  res.end(DATA);
});

server.listen(PORT, err => {
  if (err) {
    return console.log("something happened", err);
  }

  console.log("Serving data.json file on port " + PORT);
});

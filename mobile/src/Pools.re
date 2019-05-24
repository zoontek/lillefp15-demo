// Pools.re

let url = "http://localhost:8080";

type timeSlot = (string, string);
type timeSlots = array(timeSlot);
type dates = array(string);

type coordinates = {
  latitude: float,
  longitude: float,
};

type pool = {
  id: string,
  name: string,
  coordinates,
  hours: array(timeSlots),
};

type fetchedData = {
  dates,
  pools: array(pool),
};

module Decode = {
  open Json.Decode;

  let timeSlot = json => tuple2(string, string, json);
  let timeSlots = json => array(timeSlot, json);

  let coordinates = json => {
    latitude: field("latitude", float, json),
    longitude: field("longitude", float, json),
  };

  let pool = json => {
    id: field("id", string, json),
    name: field("name", string, json),
    coordinates: field("coordinates", coordinates, json),
    hours: field("hours", array(timeSlots), json),
  };

  let fetchedData = json => {
    dates: field("dates", array(string), json),
    pools: field("pools", array(pool), json),
  };
};

let fetchData = () =>
  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.json)
    |> then_(json => Decode.fetchedData(json)->resolve)
  );

open ReactNative;
include NativeElement;

type region;

[@bs.obj]
external region:
  (
    ~latitude: float,
    ~longitude: float,
    ~latitudeDelta: float,
    ~longitudeDelta: float
  ) =>
  region =
  "";

type latLng;

[@bs.obj]
external latLng: (~latitude: float, ~longitude: float) => latLng = "";

type point;

[@bs.obj] external point: (~x: float, ~y: float) => point = "";

[@react.component] [@bs.module "react-native-maps"]
external make:
  (
    ~ref: ref=?,
    ~style: Style.t=?,
    ~region: region=?,
    ~children: React.element=?
  ) =>
  React.element =
  "default";

type pressEvent =
  Event.syntheticEvent({
    .
    "coordinate": latLng,
    "position": point,
  });

module Marker = {
  [@react.component] [@bs.module "react-native-maps"]
  external make:
    (
      ~coordinate: latLng,
      ~pinColor: string=?,
      ~title: string=?,
      ~description: string=?,
      ~onPress: pressEvent => unit=?,
      unit
    ) =>
    React.element =
    "Marker";
};

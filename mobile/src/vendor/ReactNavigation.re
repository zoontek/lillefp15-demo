type navigationProp('routeParams, 'pushedParams) = {
  .
  [@bs.meth] "push": (string, 'pushedParams) => unit,
  [@bs.meth] "goBack": unit => unit,
  "state": {
    .
    "key": string,
    "routeName": string,
    "params": 'routeParams,
  },
};

type stackNavigatorConfig;

[@bs.obj]
external stackNavigatorConfig:
  (~headerMode: [@bs.string] [ | `float | `screen | `none]=?, unit) =>
  stackNavigatorConfig =
  "";

[@bs.module "react-navigation"]
external createStackNavigator:
  (Js.t('a), stackNavigatorConfig) => React.element =
  "";

[@bs.module "react-navigation"]
external createAppContainer: React.element => React.element = "";

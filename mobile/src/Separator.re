open ReactNative;

[@react.component]
let make = () =>
  <View
    style=Style.(
      style(
        ~height=pt(StyleSheet.hairlineWidth),
        ~backgroundColor=Colors.gray1,
        (),
      )
    )
  />;

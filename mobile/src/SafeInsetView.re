open ReactNative;

[@react.component]
let make = (~backgroundColor: string=?) =>
  <SafeAreaView style={Style.style(~backgroundColor, ())} />;

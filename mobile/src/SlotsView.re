open ReactNative;
open Belt;

let styles =
  StyleSheet.create(
    Style.{
      "container": style(~alignItems=`center, ~justifyContent=`center, ()),
      "line": style(~color=Colors.gray8, ~fontSize=15., ~lineHeight=22., ()),
      "closed": style(~color=Colors.red5, ()),
    },
  );

[@react.component]
let make = (~data) =>
  <View style=styles##container>
    {switch (data) {
     | [||] =>
       <Text style={Style.array([|styles##line, styles##closed|])}>
         {js|Fermé|js}->React.string
       </Text>

     | slots =>
       slots
       ->Array.mapWithIndex((i, slot) => {
           let (openAt, closeAt) = slot;
           let key = "slot-" ++ string_of_int(i);
           let text = openAt ++ " - " ++ closeAt;

           <Text key style=styles##line> text->React.string </Text>;
         })
       ->React.array
     }}
  </View>;

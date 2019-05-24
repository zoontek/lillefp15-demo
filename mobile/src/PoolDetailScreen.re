open ReactNative;
open Belt;

let styles =
  StyleSheet.create(
    Style.{
      "fill": style(~flex=1., ()),

      "header":
        style(
          ~flexDirection=`row,
          ~backgroundColor=Colors.blue6,
          ~alignItems=`center,
          ~paddingVertical=pt(16.),
          (),
        ),

      "arrow": style(~fontSize=24., ~color=Colors.white, ()),

      "title":
        style(
          ~flex=1.,
          ~fontWeight=`_600,
          ~fontSize=28.,
          ~color=Colors.white,
          (),
        ),

      "row":
        style(
          ~flexDirection=`row,
          ~padding=pt(24.),
          ~alignItems=`center,
          ~minHeight=pt(80.),
          ~justifyContent=`spaceBetween,
          (),
        ),

      "date": style(~color=Colors.gray9, ~fontSize=17., ()),
    },
  );

[@react.component]
let make =
    (
      ~navigation:
         ReactNavigation.navigationProp(PoolListScreen.detailParams, unit),
    ) => {
  let params = navigation##state##params;
  let dates = params.PoolListScreen.dates;
  let pool = params.PoolListScreen.pool;

  <View style=styles##fill>
    <StatusBar barStyle=`lightContent />
    <SafeInsetView backgroundColor=Colors.blue6 />
    <View style=styles##header>
      <TouchableOpacity
        style=styles##row onPress={_event => navigation##goBack()}>
        <Text style=styles##arrow> {js|⇠|js}->React.string </Text>
      </TouchableOpacity>
      <Text style=styles##title> pool.name->React.string </Text>
    </View>
    <Separator />
    <FlatList
      data={pool.hours}
      keyExtractor={(_item, i) => "slots-" ++ string_of_int(i)}
      renderItem={prop =>
        switch (dates[prop##index]) {
        | Some(date) =>
          <View style=styles##row>
            <Text style=styles##date> date->React.string </Text>
            <SlotsView data=prop##item />
          </View>
        | None => React.null
        }
      }
      _ItemSeparatorComponent={_props => <Separator />}
      _ListFooterComponent={_props => <SafeInsetView />}
    />
  </View>;
};

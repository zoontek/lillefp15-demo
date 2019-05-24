open Belt;
open ReactNative;

type state =
  | Loading
  | Error
  | Loaded(Pools.fetchedData);

type action =
  | FetchData
  | ReceiveError
  | ReceiveData(Pools.fetchedData);

let styles =
  StyleSheet.create(
    Style.{
      "fill": style(~flex=1., ()),

      "loaderContainer":
        style(~flex=1., ~alignItems=`center, ~justifyContent=`center, ()),

      "map": style(~width=pct(100.), ~aspectRatio=1., ()),

      "list":
        style(
          ~backgroundColor=Colors.white,
          ~marginTop=pt(-8.),
          ~borderTopLeftRadius=8.,
          ~borderTopRightRadius=8.,
          (),
        ),

      "row":
        style(
          ~flexDirection=`row,
          ~padding=pt(24.),
          ~minHeight=pt(80.),
          ~alignItems=`center,
          ~justifyContent=`spaceBetween,
          (),
        ),

      "name": style(~color=Colors.gray9, ~fontSize=17., ()),
    },
  );

[@bs.deriving jsConverter]
type detailParams = {
  dates: Pools.dates,
  pool: Pools.pool,
};

[@react.component]
let make = (~navigation: ReactNavigation.navigationProp(unit, detailParams)) => {
  let (state, dispatch) =
    React.useReducer(
      (_state, action) =>
        switch (action) {
        | FetchData => Loading
        | ReceiveError => Error
        | ReceiveData(data) => Loaded(data)
        },
      Loading,
    );

  React.useEffect1(
    () => {
      Js.Promise.(
        Pools.fetchData()
        |> then_((data: Pools.fetchedData) =>
             dispatch(ReceiveData(data))->resolve
           )
        |> catch(_err => {
             Alert.alert(
               ~title={js|Une erreur est survenue|js},
               ~message={js|Impossible d'accéder aux données|js},
               (),
             );

             dispatch(ReceiveError)->resolve;
           })
        |> ignore
      );

      None;
    },
    [||],
  );

  switch (state) {
  | Loading =>
    <View style=styles##loaderContainer>
      <ActivityIndicator size=ActivityIndicator.Size.large />
    </View>
  | Error => React.null
  | Loaded(data) =>
    <View style=styles##fill>
      <StatusBar barStyle=`darkContent />
      <MapView
        style=styles##map
        region={MapView.region(
          ~latitude=48.86,
          ~longitude=2.34,
          ~latitudeDelta=0.12,
          ~longitudeDelta=0.12,
        )}>
        {data.pools
         ->Array.mapWithIndex((i, pool) => {
             let todaySlots = pool.hours[0]->Option.getWithDefault([||]);

             <MapView.Marker
               key={pool.id ++ "-" ++ string_of_int(i)}
               coordinate={MapView.latLng(
                 ~latitude=pool.coordinates.latitude,
                 ~longitude=pool.coordinates.longitude,
               )}
               pinColor=Colors.blue6
               title={pool.name}
               description={
                 switch (todaySlots) {
                 | [||] => {js|Fermé|js}
                 | slots =>
                   slots->Array.map(slot => {
                     let (openAt, closeAt) = slot;
                     openAt ++ " - " ++ closeAt;
                   })
                   |> Js.Array.joinWith(" / ")
                 }
               }
             />;
           })
         ->React.array}
      </MapView>
      <FlatList
        data={data.pools}
        style=styles##list
        keyExtractor={(item, _i) => item.id}
        renderItem={prop => {
          let item = prop##item;
          let todaySlots = item.hours[0]->Option.getWithDefault([||]);

          <TouchableOpacity
            style=styles##row
            onPress={_event =>
              navigation##push("detail", {dates: data.dates, pool: item})
            }>
            <Text style=styles##name> {item.name}->React.string </Text>
            <SlotsView data=todaySlots />
          </TouchableOpacity>;
        }}
        _ItemSeparatorComponent={_props => <Separator />}
        _ListFooterComponent={_props => <SafeInsetView />}
      />
    </View>
  };
};

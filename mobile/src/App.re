let stackNavigator =
  ReactNavigation.(
    createStackNavigator(
      {"list": PoolListScreen.make, "detail": PoolDetailScreen.make},
      stackNavigatorConfig(~headerMode=`none, ()),
    )
  );

let default = ReactNavigation.createAppContainer(stackNavigator);

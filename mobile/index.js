import { AppRegistry } from "react-native";
import App from "./src/App.bs.js";
import { name as appName } from "./app.json";

AppRegistry.registerComponent(appName, () => App);

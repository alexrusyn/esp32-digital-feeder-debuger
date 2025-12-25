import { ChakraProvider } from "@chakra-ui/react";
import { RouterProvider } from "react-router";

import { system } from "./theme";
import { router } from "./routes";

const App = () => (
  <ChakraProvider value={system}>
    <RouterProvider router={router} />
  </ChakraProvider>
);

export default App;

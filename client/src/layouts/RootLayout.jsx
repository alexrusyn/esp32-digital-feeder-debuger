import { Flex, Container } from "@chakra-ui/react";

import { Outlet } from "react-router";

import Sidebar from "./Sidebar";
import Topbar from "./Topbar";

const RootLayout = () => (
  <Flex minH="100vh" bg="bg.muted" direction="column">
    <Topbar />
    <Flex flex="1">
      <Sidebar />
      <Container p="4">
        <Outlet />
      </Container>
    </Flex>
  </Flex>
);

export default RootLayout;

import { Box, Center } from "@chakra-ui/react";

import { Outlet } from "react-router";

const AuthLayout = () => (
  <Center h="100vh" bg="gray.100">
    <Box bg="white" p={8} rounded="xl" shadow="md">
      <Outlet />
    </Box>
  </Center>
);

export default AuthLayout;

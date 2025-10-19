import { Flex, Heading, Spacer, IconButton } from "@chakra-ui/react";

import { MdLogout } from "react-icons/md";

const Topbar = () => (
  <Flex bg="white" align="center" p={4}>
    <Heading>ESP32 Control Panel</Heading>
    <Spacer />
    {/* <IconButton variant="ghost" aria-label="Logout">
      <MdLogout />
    </IconButton> */}
  </Flex>
);

export default Topbar;

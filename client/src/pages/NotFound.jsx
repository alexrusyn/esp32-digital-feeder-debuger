import { VStack, Center, Heading, Button } from "@chakra-ui/react";

import { Link } from "react-router";

const NotFountPage = () => (
  <Center h="100vh" bg="bg.muted">
    <VStack bg="white" p="8" rounded="md" gap="4">
      <Heading>Page not found</Heading>
      <Link to="/">
        <Button>Back to home</Button>
      </Link>
    </VStack>
  </Center>
);

export default NotFountPage;

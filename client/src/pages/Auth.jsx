import {
  VStack,
  Box,
  Heading,
  PinInput,
  HStack,
  Button,
  Text,
} from "@chakra-ui/react";

import { useState } from "react";

export default function Auth() {
  const [pin, setPin] = useState(["", "", "", "", "", ""]);

  const handleLogin = () => {
    if (pin === "123456") {
    } else {
    }
  };

  return (
    <VStack bg="white" p={8} borderRadius="xl" shadow="lg" spacing={4}>
      <Heading size="md">Enter PIN</Heading>
      <HStack>
        <PinInput.Root value={pin} onValueChange={(e) => setPin(e.value)}>
          <PinInput.HiddenInput />
          <PinInput.Control>
            <PinInput.Input index={0} />
            <PinInput.Input index={1} />
            <PinInput.Input index={2} />
            <PinInput.Input index={3} />
            <PinInput.Input index={4} />
            <PinInput.Input index={5} />
          </PinInput.Control>
        </PinInput.Root>
      </HStack>
      <Button colorScheme="blue" w="full" onClick={handleLogin}>
        Login
      </Button>
      <Text fontSize="sm" color="gray.500">
        Default PIN: 1234
      </Text>
    </VStack>
  );
}

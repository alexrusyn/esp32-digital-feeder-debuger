import React from "react";

import { Card as ChakraCard, HStack, Spacer, Heading } from "@chakra-ui/react";

const Card = ({
  children,
  label = "Card Header",
  headerActions = null,
  actions = null,
  Icon = null,
}) => (
  <ChakraCard.Root>
    <ChakraCard.Header p={4} pb={0}>
      <HStack>
        <HStack align="center">
          {Icon}
          <Heading>{label}</Heading>
        </HStack>
        <Spacer />
        {headerActions && <HStack>{headerActions}</HStack>}
      </HStack>
    </ChakraCard.Header>
    <ChakraCard.Body p={4}>{children}</ChakraCard.Body>
    {actions && (
      <ChakraCard.Footer p={4} pt={0}>
        {actions}
      </ChakraCard.Footer>
    )}
  </ChakraCard.Root>
);

export default Card;

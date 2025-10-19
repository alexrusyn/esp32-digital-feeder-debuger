import { VStack, HStack, Box, Spacer, Heading, Text } from "@chakra-ui/react";

const Section = ({
  title,
  description,
  children,
  actions = null,
  noBg = false,
}) => (
  <VStack
    align="stretch"
    bg={noBg ? "" : "bg"}
    borderRadius="md"
    p={noBg ? 0 : 4}
    gap={4}
    mb={6}
  >
    <HStack>
      <Box>
        <Heading>{title}</Heading>
        {description && <Text textStyle="xs">{description}</Text>}
      </Box>
      <Spacer />
      {actions}
    </HStack>
    {children}
  </VStack>
);

export default Section;

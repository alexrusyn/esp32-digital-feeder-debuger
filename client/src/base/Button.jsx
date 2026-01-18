import { Button as ChakraButton } from "@chakra-ui/react";

const Button = ({ children, onClick }) => {
  return (
    <ChakraButton size="md" onClick={onClick}>
      {children}
    </ChakraButton>
  );
};

export default Button;

import { useState, useCallback } from "react";

import { HStack, IconButton, NumberInput } from "@chakra-ui/react";
import { LuMinus, LuPlus } from "react-icons/lu";

const NumericInput = ({ onChange, defaultValue = 0, min = 0, max = 100 }) => {
  const [value, setValue] = useState(defaultValue);

  const onChangeHanlder = useCallback((e) => {
    const newValue = Number(e.value);

    setValue(newValue);
    onChange(newValue);
  }, []);

  return (
    <NumberInput.Root
      value={value}
      onValueChange={onChangeHanlder}
      min={min}
      max={max}
    >
      <HStack gap="2">
        <NumberInput.DecrementTrigger asChild>
          <IconButton variant="outline" size="sm">
            <LuMinus />
          </IconButton>
        </NumberInput.DecrementTrigger>
        <NumberInput.ValueText textAlign="center" fontSize="lg" minW="3ch" />
        <NumberInput.IncrementTrigger asChild>
          <IconButton variant="outline" size="sm">
            <LuPlus />
          </IconButton>
        </NumberInput.IncrementTrigger>
      </HStack>
    </NumberInput.Root>
  );
};

export default NumericInput;

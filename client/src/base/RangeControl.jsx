import { useCallback } from "react";

import { HStack, Slider } from "@chakra-ui/react";

const RangeControl = ({
  label,
  value,
  onChange,
  onChangeEnd,
  min = 0,
  max = 100,
}) => {
  const valueChangeHandler = useCallback(
    ({ value }) => {
      if (value && typeof onChange === "function") {
        onChange(value[0]);
      }
    },
    [onChange]
  );

  const valueChangeEndHandler = useCallback(
    ({ value }) => {
      if (value && typeof onChangeEnd === "function") {
        onChangeEnd(value[0]);
      }
    },
    [onChangeEnd]
  );

  return (
    <Slider.Root
      maxW="sm"
      size="sm"
      defaultValue={[value]}
      onValueChange={valueChangeHandler}
      onValueChangeEnd={valueChangeEndHandler}
      min={min}
      max={max}
    >
      <HStack justify="space-between">
        <Slider.Label>{label}</Slider.Label>
        <Slider.ValueText />
      </HStack>
      <Slider.Control>
        <Slider.Track>
          <Slider.Range />
        </Slider.Track>
        <Slider.Thumbs rounded="l1" />
      </Slider.Control>
    </Slider.Root>
  );
};

export default RangeControl;

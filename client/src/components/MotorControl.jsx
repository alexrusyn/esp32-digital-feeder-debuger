import { VStack, Text, HStack } from "@chakra-ui/react";
import { useState } from "react";

import NumericInput from "../base/NumericInput";
import RangeControl from "../base/RangeControl";

const MotorControl = () => {
  const [speed, setSpeed] = useState(50);
  const [position, setPosition] = useState(0);

  return (
    <VStack align="stretch" spacing={4}>
      <RangeControl
        label="Speed"
        value={speed}
        onChangeEnd={setSpeed}
        min={0}
        max={100}
      />

      <HStack>
        <Text>Position:</Text>
        <NumericInput
          value={position}
          onChange={setPosition}
          min={0}
          max={360}
        />
      </HStack>
    </VStack>
  );
};

export default MotorControl;

import { Status } from "@chakra-ui/react";

import {
  Card,
  RangeControl,
  NumericInput,
  SwitchInput,
  CircularSliderInput,
} from "../base";

const CONTROLS_COMPONENT_BY_TYPE = {
  switch: SwitchInput,
  number: NumericInput,
  slider: RangeControl,
  circularSlider: CircularSliderInput,
};

const NullComponent = () => null;

const ControlTile = ({ label, type, controlProps, isActive = null }) => {
  const Control =
    type in CONTROLS_COMPONENT_BY_TYPE
      ? CONTROLS_COMPONENT_BY_TYPE[type]
      : NullComponent;

  return (
    <Card
      label={label}
      headerActions={
        isActive !== null && (
          <Status.Root colorPalette={isActive ? "blue" : "red"}>
            <Status.Indicator />
          </Status.Root>
        )
      }
    >
      <Control {...controlProps} />
    </Card>
  );
};

export default ControlTile;

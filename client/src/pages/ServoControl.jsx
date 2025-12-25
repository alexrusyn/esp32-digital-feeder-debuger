import { Section } from "../layouts";

import { CircularSliderInput } from "../base";
import { ControlTile } from "../components";

export default function LedControl() {
  return (
    <Section title="Servo Control" noBg>
      <ControlTile
        label="Test number control"
        type="number"
        controlProps={{
          onChange: (val) => console.log("numeric change", val),
          min: 0,
          max: 20,
        }}
      />
      <ControlTile
        label="Test slider control"
        type="slider"
        controlProps={{
          label: "Slider test",
          value: 10,
          onChangeEnd: (pos) => console.log("slider end", pos),
          min: -50,
          max: 50,
        }}
      />
      <ControlTile
        label="Test circular slider control"
        type="circularSlider"
        controlProps={{
          onChangeEnd: (angle) => console.log("circular slider end", angle),
        }}
      />
    </Section>
  );
}

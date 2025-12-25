import { Section } from "../layouts";

import { ControlTile } from "../components";

import useLed from "../api/hooks/useLed";

const LedControl = () => {
  const { isLedOn, toggleLedState } = useLed();

  return (
    <Section title="LED Controls" noBg>
      <ControlTile
        label="LED Toggle"
        type="switch"
        isActive={isLedOn}
        controlProps={{
          name: "led",
          label: "Toggle led",
          checked: isLedOn,
          onCheckedChange: () => toggleLedState(!isLedOn),
        }}
      />
    </Section>
  );
};

export default LedControl;

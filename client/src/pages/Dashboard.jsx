import { ControlTile, InfoTile, DashboardSection } from "../components";

import useLed from "../api/hooks/useLed";

export default function Dashboard() {
  const { isLedOn, toggleLedState } = useLed();

  return (
    <>
      <DashboardSection title="LED Controls" to="/led">
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
      </DashboardSection>
    </>
  );
}

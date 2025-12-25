import { Switch } from "@chakra-ui/react";

const SwitchInput = ({ name, label, checked, onCheckedChange }) => (
  <Switch.Root name={name} checked={checked} onCheckedChange={onCheckedChange}>
    <Switch.HiddenInput />
    <Switch.Control>
      <Switch.Thumb />
    </Switch.Control>
    <Switch.Label>{label}</Switch.Label>
  </Switch.Root>
);

export default SwitchInput;

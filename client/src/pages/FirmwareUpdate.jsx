import { useState } from "react";

import { Section } from "../layouts";

import { SelectList } from "../components";

import { Card, Button } from "../base";

const data = [
  { label: "v0.2.1", value: "v0.2.1", type: "Testing" },
  { label: "v0.2.0", value: "v1.2.0", type: "Released" },
  { label: "v0.1.0", value: "v0.1.0", type: "Released" },
  { label: "v0.0.0", value: "v0.0.0", type: "Released" },
];

const FirmwareUpdate = () => {
  const [version, setVersion] = useState("");

  return (
    <Section title="Firmware Update" noBg>
      <Card
        label="Available versions"
        actions={<Button onClick={() => console.log(version)}>Update</Button>}
      >
        <SelectList
          value={version}
          setValue={setVersion}
          items={data}
          placeholder="Start type for search version"
        />
      </Card>
    </Section>
  );
};

export default FirmwareUpdate;

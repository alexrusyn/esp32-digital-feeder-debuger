import { useEffect, useState } from "react";

import { useGithubReleases } from "../api/githubApi";

import { Section } from "../layouts";

import { SelectList } from "../components";

import { Card, Button } from "../base";

const FirmwareUpdate = () => {
  const [selectedVersion, setSelectedVersion] = useState("");

  const releases = useGithubReleases();

  return (
    <Section title="Firmware Update" noBg>
      <Card
        label="Available versions"
        actions={
          <Button onClick={() => console.log(selectedVersion)}>Update</Button>
        }
      >
        <SelectList
          value={selectedVersion}
          setValue={setSelectedVersion}
          data={releases}
          placeholder="Start type for search version"
        />
      </Card>
    </Section>
  );
};

export default FirmwareUpdate;

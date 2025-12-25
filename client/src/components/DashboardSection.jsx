import { SimpleGrid, Icon } from "@chakra-ui/react";
import { Link } from "react-router";

import { Section } from "../layouts";

import { MdLaunch } from "react-icons/md";

const DashboardSection = ({ title, children, to = null }) => (
  <Section
    title={title}
    actions={
      to && (
        <Link to={to}>
          <Icon size="md" color="gray.solid">
            <MdLaunch />
          </Icon>
        </Link>
      )
    }
    noBg
  >
    <SimpleGrid
      columns={{ base: 1, sm: 2, md: 3, xl: 4 }}
      gap={{ base: 2, md: 3, xl: 4 }}
    >
      {children}
    </SimpleGrid>
  </Section>
);

export default DashboardSection;

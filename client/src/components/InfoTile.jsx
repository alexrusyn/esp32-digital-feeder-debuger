import { Icon } from "@chakra-ui/react";
import { Link } from "react-router";

import Card from "../base/Card";

import { MdLaunch } from "react-icons/md";

const InfoTile = ({ label, children, to }) => (
  <Card
    label={label}
    headerActions={
      to && (
        <Link to={to}>
          <Icon size="sm" color="gray.solid">
            <MdLaunch />
          </Icon>
        </Link>
      )
    }
  >
    {children}
  </Card>
);

export default InfoTile;

import { VStack, IconButton, Spacer } from "@chakra-ui/react";
import { Link, useLocation } from "react-router";

import {
  MdDashboardCustomize,
  MdOutlineLightbulb,
  MdLoupe,
  MdSettings,
} from "react-icons/md";

const links = [
  { to: "/", label: "Dashboard", Icon: MdDashboardCustomize },
  { to: "/led", label: "Led Control", Icon: MdOutlineLightbulb },
  { to: "/servo", label: "Servo Control", Icon: MdLoupe },
];

const ButtonLink = ({ to, label, children, isActive }) => (
  <Link to={to} key={label}>
    <IconButton
      variant={isActive ? "solid" : "ghost"}
      aria-label={label}
      borderRadius="xl"
    >
      {children}
    </IconButton>
  </Link>
);

const Sidebar = () => {
  const location = useLocation();

  const getIsActive = (to) => location.pathname === to;

  return (
    <VStack w="70px" minH="100%" bg="bg" gap={4} p={4}>
      {links.map(({ to, label, Icon }) => (
        <ButtonLink to={to} key={label} isActive={getIsActive(to)}>
          <Icon />
        </ButtonLink>
      ))}
      <Spacer />
      <ButtonLink
        to={"/settings"}
        key="Settings"
        isActive={getIsActive("/settings")}
      >
        <MdSettings />
      </ButtonLink>
    </VStack>
  );
};

export default Sidebar;

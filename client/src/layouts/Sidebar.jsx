import { VStack, IconButton, Spacer } from "@chakra-ui/react";
import { Link, useLocation } from "react-router";

import {
  MdDashboardCustomize,
  MdOutlineLightbulb,
  MdLoupe,
  MdSettings,
  MdBrowserUpdated,
} from "react-icons/md";
import { useCallback } from "react";

const links = [
  { to: "/", label: "Dashboard", Icon: MdDashboardCustomize },
  { to: "/led", label: "Led Control", Icon: MdOutlineLightbulb },
  { to: "/servo", label: "Servo Control", Icon: MdLoupe },
];

const adminLinks = [
  { to: "/update", label: "Firmware Update", Icon: MdBrowserUpdated },
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

  const getIsActive = useCallback((to) => location.pathname === to, [location]);

  const renderLinks = useCallback(
    (linkList) =>
      linkList.map(({ to, label, Icon }) => (
        <ButtonLink to={to} key={label} isActive={getIsActive(to)}>
          <Icon />
        </ButtonLink>
      )),
    [getIsActive]
  );

  return (
    <VStack w="70px" minH="100%" bg="bg" gap={4} p={4}>
      {renderLinks(links)}
      <Spacer />
      {renderLinks(adminLinks)}
    </VStack>
  );
};

export default Sidebar;

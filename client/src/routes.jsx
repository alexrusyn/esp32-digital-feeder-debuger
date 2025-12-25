import { createHashRouter } from "react-router";

import RootLayout from "./layouts/RootLayout";
import AuthLayout from "./layouts/AuthLayout";

import Dashboard from "./pages/Dashboard";
import LedControl from "./pages/LedControl";
import ServoControl from "./pages/ServoControl";
import Auth from "./pages/Auth";
import NotFountPage from "./pages/NotFound";

const protectedLoader = () => {
  return false;
};

const authLoader = () => {
  return true;
};

export const router = createHashRouter([
  {
    path: "/",
    element: <RootLayout />,
    loader: protectedLoader,
    children: [
      { index: true, element: <Dashboard /> },
      { path: "led", element: <LedControl /> },
      { path: "servo", element: <ServoControl /> },
    ],
  },
  {
    path: "/auth",
    element: <AuthLayout />,
    loader: authLoader,
    children: [{ index: true, element: <Auth /> }],
  },
  {
    path: "*",
    exact: true,
    element: <NotFountPage />,
  },
]);

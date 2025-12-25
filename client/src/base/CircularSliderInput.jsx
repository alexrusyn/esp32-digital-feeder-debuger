import { useRef, useState, useEffect } from "react";
import { Box, Text } from "@chakra-ui/react";

const CircularSliderInput = ({ onChange, onChangeEnd }) => {
  const centerRef = useRef(null);

  const [angle, setAngle] = useState(0);
  const [isDragging, setIsDragging] = useState(false);

  const handleMove = (e) => {
    if (!isDragging) return;

    const rect = centerRef.current.getBoundingClientRect();
    const cx = rect.left + rect.width / 2;
    const cy = rect.top + rect.height / 2;

    const x = e.clientX - cx;
    const y = e.clientY - cy;

    let newAngle = Math.atan2(y, x) * (180 / Math.PI) + 90;
    if (newAngle < 0) newAngle += 360;

    const roundedAngle = Math.round(newAngle);

    setAngle(roundedAngle);
    onChange?.(roundedAngle);
  };

  const handleMouseDown = () => setIsDragging(true);
  const handleMouseUp = () => {
    if (isDragging) onChangeEnd?.(angle);
    setIsDragging(false);
  };

  useEffect(() => {
    window.addEventListener("mousemove", handleMove);
    window.addEventListener("mouseup", handleMouseUp);
    return () => {
      window.removeEventListener("mousemove", handleMove);
      window.removeEventListener("mouseup", handleMouseUp);
    };
  });

  return (
    <Box>
      <Box
        ref={centerRef}
        position="relative"
        w="120px"
        h="120px"
        bg="gray.muted"
        shadow="inset"
        borderRadius="full"
        cursor="pointer"
        onMouseDown={handleMouseDown}
      >
        <Box
          position="absolute"
          top="10px"
          left="59px"
          w="2px"
          h="50px"
          bg="black"
          borderRadius="xl"
          transformOrigin="bottom center"
          transform={`rotate(${angle}deg)`}
        />
      </Box>
      <Text>{angle}°</Text>
    </Box>
  );
};

export default CircularSliderInput;

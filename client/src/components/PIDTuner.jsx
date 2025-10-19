import { useState, useEffect } from "react";
import { Box, Flex, Text, SimpleGrid, GridItem } from "@chakra-ui/react";

import { Chart, useChart } from "@chakra-ui/charts";

import { LineChart, Line, XAxis, YAxis, Legend, CartesianGrid } from "recharts";

import { RangeControl, NumericInput } from "../base";

const PIDTuner = () => {
  const [Kp, setKp] = useState(0.1);
  const [Ki, setKi] = useState(10);
  const [Kd, setKd] = useState(0);
  const [setpoint, setSetpoint] = useState(50);

  const chart = useChart({
    data: [
      { time: 0, input: 0, output: 0, setpoint: 50 },
      { time: 1, input: 1, output: 2, setpoint: 50 },
      { time: 2, input: 2, output: 10, setpoint: 40 },
      { time: 5, input: 10, output: 15, setpoint: 15 },
    ],
    series: [
      {
        type: "monotype",
        key: "input",
        color: "#48acf0",
        label: "Control Input",
      },
      {
        type: "monotype",
        key: "output",
        color: "#f06543",
        label: "Control Input",
      },
      {
        type: "monotype",
        key: "setpoint",
        color: "#4e5340",
        label: "Control Input",
      },
    ],
  });

  return (
    <SimpleGrid columns={{ base: 1, md: 4 }} gap={4}>
      <GridItem colSpan={{ base: 1, md: 1 }}>
        <Box>
          <Text>Setpoint: {setpoint}</Text>
          <RangeControl
            min={0}
            max={200}
            value={setpoint}
            onChangeEnd={setSetpoint}
          />
        </Box>
        <Box>
          <Text>Kp: {Kp}</Text>
          <RangeControl
            min={0}
            max={5}
            step={0.1}
            value={Kp}
            onChangeEnd={setKp}
          />
        </Box>
        <Box>
          <Text>Ki: {Ki}</Text>
          <RangeControl
            min={0}
            max={50}
            step={1}
            value={Ki}
            onChangeEnd={setKi}
          />
        </Box>
        <Box>
          <Text>Kd: {Kd}</Text>
          <RangeControl
            min={0}
            max={5}
            step={0.1}
            value={Kd}
            onChangeEnd={setKd}
          />
        </Box>
        <Flex gap={4}>
          <Box>
            <Text fontSize="sm">Noise</Text>
            <NumericInput size="sm" min={0} max={10} value={1} />
          </Box>
          <Box>
            <Text fontSize="sm">Sample time (ms)</Text>
            <NumericInput size="sm" min={10} max={500} value={50} />
          </Box>
        </Flex>
      </GridItem>
      <GridItem colSpan={{ base: 1, md: 3 }}>
        <Chart.Root chart={chart} maxH="600px">
          <LineChart data={chart.data}>
            <CartesianGrid />
            <XAxis dataKey="time" hide />
            <YAxis domain={["dataMin - 50", "dataMax + 50"]} />
            <Legend />
            {chart.series.map(({ type, key, color, label }) => (
              <Line
                key={key}
                type={type}
                dataKey={key}
                stroke={color}
                name={label}
              />
            ))}
          </LineChart>
        </Chart.Root>
      </GridItem>
    </SimpleGrid>
  );
};

export default PIDTuner;

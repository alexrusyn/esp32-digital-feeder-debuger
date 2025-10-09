import { useCallback } from "react";

import useLed from "./api/hooks/useLed";

const App = () => {
    const { isLedOn, toggleLedState } = useLed();

    const clickHandler = useCallback(
        () => toggleLedState(!isLedOn),
        [isLedOn]
    );

    return (
        <div>
            <button onClick={clickHandler}>Toogle led</button>
            <span>{isLedOn ? 'ON' : 'OFF'}</span>
        </div>
    )
}

export default App;

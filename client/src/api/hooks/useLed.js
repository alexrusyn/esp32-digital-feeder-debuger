import { useEffect, useState, useCallback } from 'react';

import ledController from '../controllers/led';

const useLed = () => {
    const [isLedOn, setIsLedOn] = useState(false);

    const toggleLedState = useCallback((newState) => {
        ledController.setState(newState)
            .then((data) => {
                console.info(data.message);
                setIsLedOn(newState);
            })
            .catch((e) => console.error(e.message))
    }, []);

    useEffect(() => {
        ledController.getState()
            .then(({ data }) => setIsLedOn(data.isLedOn))
            .catch((e) => console.error(e.message));
    }, []);

    return { isLedOn, toggleLedState };
}

export default useLed;

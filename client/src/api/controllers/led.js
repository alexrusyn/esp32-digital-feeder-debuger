import httpClient from '../httpClient';

const getState = () => httpClient('/test/status');

const setState = (payload) =>
    httpClient('/test/toggle', { method: 'POST', body: { isLedOn: payload } });

export default {
    getState,
    setState,
}

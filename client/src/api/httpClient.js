const API_BASE = 'http://192.168.0.33/api';

async function httpClient(endpoint, { method = 'GET', body = null, headers } = {}) {
    const config = {
        method,
        headers: {
            'X-Api-Key': API_KEY,
            "Content-Type": "application/json",
            ...headers
        },
        ...(body && { body: JSON.stringify(body) })
    };

    const response = await fetch(`${API_BASE}${endpoint}`, config);

    if (!response.ok) {
        const error = await response.json()
        throw new Error(error.message || 'Request failed');
    }

    return response.json();
}

export default httpClient;


// where is fetch api defined
/**
 * The Fetch API is defined in the browser environment and is used to make HTTP requests.
 */

import fetch from 'node-fetch';

const httpClient = {
    get: (url, options) => {
        fetch(url, {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json',
            },
        })
            .then((res) => res.json())
            .then((data) => console.log(data))
            .catch((err) => console.log(err));
    },
    post: (url, data, options) => {
        fetch(url, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: data,
        })
            .then((res) => res.json())
            .then((data) => console.log(data))
            .catch((err) => console.log(err));
    },
};

const triggerRaw = (payload) => {
    if (typeof payload === 'string') {
        httpClient.post("http://localhost:3333/api/v1/raw", payload);
    } else {
        httpClient.post("http://localhost:3333/api/v1/raw", JSON.stringify(payload));
    }
}


const triggerEvent = (eventName) => {
    httpClient.post("http://localhost:3333/api/v1/trigger-event", eventName );
}

export {
    httpClient,
    triggerRaw,
    triggerEvent
};

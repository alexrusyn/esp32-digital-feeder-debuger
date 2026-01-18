import { useEffect, useState, useCallback } from "react"; 

const API_BASE = 'https://api.github.com/repos';

async function getReleases({ user, repo }) {
    const response = await fetch(`${API_BASE}/${user}/${repo}/releases`);

    if (!response.ok) {
        const error = await response.json()
        throw new Error(error.message || 'Request failed');
    }

    return response.json();
}

const transformReleaseData = (data) =>
    data.map((release) => ({
        label: release.name,
        value: release.tag_name,
        published: release.published_at,
        updated: release.updated_at,
        type: release.prerelease ? "Pre-released" : "Released"
    }))

export const useGithubReleases = () => {
    const [data, setData] = useState([]);
    
    const getReleasesData = useCallback(() => getReleases({
        user: GITHUB_USER,
        repo: GITHUB_REPO,
    }).then((res) => setData(transformReleaseData(res))), []);

    useEffect(() => {
        getReleasesData();
    }, []);

    return data;
}

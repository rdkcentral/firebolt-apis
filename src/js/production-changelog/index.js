const path = require('path');
const { readFile, writeFile, ensureFile } = require('fs-extra');

const getConfig = ({ changelogFile, changelogTitle }) => ({
    changelogFile: !changelogFile ? 'CHANGELOG.md' : changelogFile,
    changelogTitle,
});

async function prepare(config, { cwd, nextRelease, logger }) {
    const notes = nextRelease.notes
    const { changelogFile, changelogTitle } = getConfig(config)
    const logPath = path.resolve(cwd, changelogFile)

    // scrub prerelease notes if this release is not a prerelease
    if (notes) {
        await ensureFile(logPath)
        const currentFile = (await readFile(logPath)).toString().trim()

        let content =
            changelogTitle && currentFile.startsWith(changelogTitle)
                ? currentFile.slice(changelogTitle.length).trim()
                : currentFile;

        if (nextRelease.channel === 'latest') {
            logger.log(`Scrubbing prerelease notes from ${logPath}.`)

            // Looking for things like:
            //# [0.10.0-next.5](https://github.com/rdkcentral/firebolt-core-sdk/compare/v0.10.0-next.4...v0.10.0-next.5) (2023-02-01)
            const regex = /\# \[[0-9]+\.[0-9]+\.[0-9]+\-[^\]]+\].*?\n+\# /gms
            while (content.match(regex)) {
                content = content.replace(regex, '\n# ')
            }
        }

        content = `${notes.trim()}\n${content ? `\n${content}\n` : ''}`;

        logger.log(`Writing changelog file: ${logPath}`)

        await writeFile(logPath, changelogTitle ? `${changelogTitle}\n\n${content}` : content);
    }
}

module.exports = { prepare };

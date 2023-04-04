const path = require('path');
const { readFile, writeFile, ensureFile } = require('fs-extra');

const resolveConfig = ({ changelogFile, changelogTitle }) => ({
    changelogFile: !changelogFile ? 'CHANGELOG.md' : changelogFile,
    changelogTitle,
});

async function prepare(pluginConfig, { cwd, nextRelease: { notes }, logger }) {
    const { changelogFile, changelogTitle } = resolveConfig(pluginConfig);
    const changelogPath = path.resolve(cwd, changelogFile);

    if (notes) {
        await ensureFile(changelogPath);
        const currentFile = (await readFile(changelogPath)).toString().trim();

        if (currentFile) {
            logger.log('Update %s', changelogPath);
        } else {
            logger.log('Create %s', changelogPath);
        }

        let currentContent =
            changelogTitle && currentFile.startsWith(changelogTitle)
                ? currentFile.slice(changelogTitle.length).trim()
                : currentFile;

        logger.log("Scrubbing prerelease notes.")

        // Looking for things like:
        //# [0.10.0-next.5](https://github.com/rdkcentral/firebolt-core-sdk/compare/v0.10.0-next.4...v0.10.0-next.5) (2023-02-01)
        const regex = /\# \[[0-9]+\.[0-9]+\.[0-9]+\-[^\]]+\].*?\n+\# /gms
        while (currentContent.match(regex)) {
            currentContent = currentContent.replace(regex, '\n# ')
        }

        let content = `${notes.trim()}\n${currentContent ? `\n${currentContent}\n` : ''}`;

        await writeFile(changelogPath, changelogTitle ? `${changelogTitle}\n\n${content}` : content);
    }
}

module.exports = { prepare };

export default [
    {
        ignores: [
            'src/sdks/*/build/**',
            'src/sdks/*/dist/**',
            'src/sdks/*/test/transpiled-suite/**',
            'dist/**',
            'node_modules/**',
        ],
    },
    {
        files: [
            'src/**/*.mjs',
            'src/**/*.js',
            'test/**/*.mjs',
            'test/**/*.js',
        ],
        ignores: [
            // Hand-written .js test files are paired with .ts counterparts;
            // unused-param issues in callbacks are already caught by tsc noUnusedLocals on the .ts files.
            'src/sdks/*/test/suite/*.test.js',
        ],
        languageOptions: {
            ecmaVersion: 2022,
            sourceType: 'module',
        },
        rules: {
            'no-unused-vars': ['error', { argsIgnorePattern: '^_', varsIgnorePattern: '^_' }],
        },
    },
]

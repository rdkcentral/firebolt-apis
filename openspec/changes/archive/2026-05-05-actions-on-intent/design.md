## Trait choice

`@event` — the platform initiates intent delivery; apps subscribe and receive the value
pushed at runtime. There is no getter (apps don't poll for the current intent), so a
property trait would be incorrect.

## Type decisions

`String` — the payload is the intent string directly. No wrapper structure is needed
since there is only one field to deliver.

## Notes

The existing `start` operation on `ActionsService` goes app → platform (app sends an
intent to start). `onIntent` goes the other direction: platform → app. These are
complementary, not overlapping.

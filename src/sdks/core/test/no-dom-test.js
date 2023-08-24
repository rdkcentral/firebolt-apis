// This test ensures that Firebolt doesn't complain/crash when run in DOM-less environments
import { Lifecycle } from '../build/javascript/src/firebolt.mjs';
Lifecycle.ready()

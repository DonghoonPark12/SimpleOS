```mermaid
graph TD
    PAUSE --Play/Pause--> PLAY
    PAUSE --Stop      --> IDLE
    IDLE  --Play/Pause--> PLAY
    PLAY  --Stop      --> IDLE
    PLAY  --Play/Pause--> PAUSE

```

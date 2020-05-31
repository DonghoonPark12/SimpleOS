```mermaid
graph TD
    PAUSE --Play/Pause--> PLAY
    PAUSE --Stop      --> IDLE
    PLAY  --Stop      --> IDLE
    PLAY  --Play/Pause--> PAUSE
    IDLE  --Play/Pause--> PLAY
```

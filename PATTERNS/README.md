```mermaid
graph TD
    IDLE --Play/Pause--> PLAY
    PLAY --Stop-->IDLE
    PLAY --Play/Pause--> PAUSE
    PAUSE --Play/Pause--> PLAY
    PAUSE --Stop-->IDLE
```

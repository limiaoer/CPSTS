# CPSTS
Resource Modeling and Security Verification System for CPS Temporal Constraints

The CPSTS system is a resource modeling and security verification system designed for CPS. In this system, process events are transformed into bipartite graph models, which are subject to temporal constraints. The system supports users in creating and modifying process events, converting them into bipartite graph models for temporal security verification. The system interface is clear and user-friendly, facilitating ease of use. Users can create, edit, save, and verify process events and bipartite graph models using the operation buttons on the interface. Only one process event or bipartite graph model can be processed at a time, and upon importing new events or models, the system automatically clears all windows. Verification results are saved in a folder and displayed on the system interface. Users can modify the bipartite graph models based on the verification results to ensure compliance with temporal security constraints. Additionally, the bipartite graph models are saved in a folder for future use. The system also supports operations such as copy, paste, select all, cut, undo, and redo, making model manipulation convenient for users.

In summary, this system provides a convenient and efficient way to establish CPS resource models and conduct temporal security verification. It is user-friendly and practical, aimed at assisting users in better understanding and analyzing the design and performance of CPS systems. 

| master

---| CPSTS  //Release version of the software

------| bigraph //bipartite graph models

------| processEvent  //process events

------| tesingRes  //test results

------| CPSMC  //software launch portal

---| CPSTS-QT  //software source code, including front-end and back-end

------| bigraph

------| img

------| processEvent

------| testingRes

------| main.cpp

------| mainwindow.cpp //front-end

------| mainwindow.h

------| test.cpp  //back-end:model verification

------| test.h

------| translate.cpp  //back-end:model transformation

------| translate.h

The source of the paper for this project is Chen XY, Zhu Y, Zhao Y, Wang JY. "Modeling and safety verification method for CPS topology and time constrained resource." Journal of Software, 2022 (in Chinese).http://www.jos.org.cn/1000-9825/6600.htm

This project is supported by the CCF-Huawei Innovative Research Program (CCF-HuaweiFM202209).

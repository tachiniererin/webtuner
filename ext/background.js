
function onError(error) {
    console.log(`Error: ${error}`);
}

function tabLeft(tabs) {
    doStore = false;
    for (let i = 0; i < tabs.length; i++) {
        const tab = tabs[i];
        if (tab.active && i > 0) {
            var updating = browser.tabs.update(tabs[i - 1].id, {
                active: true
            });
            return;
        }
    }
}

function tabRight(tabs) {
    doStore = false;
    for (let i = 0; i < tabs.length; i++) {
        const tab = tabs[i];
        if (tab.active && i < tabs.length - 1) {
            var updating = browser.tabs.update(tabs[i + 1].id, {
                active: true
            });
            return;
        }
    }
}

function tabClose(tabs) {
    doStore = false;
    for (let i = 0; i < tabs.length; i++) {
        const tab = tabs[i];
        if (tab.active) {
            browser.tabs.remove(tabs[i].id);

            // Remove the closed tab from the stored tabs list
            for (let k = 0; k < storedTabs.length; k++) {
                if (storedTabs[k] == tabs[i].id){
                    storedTabs[k] = -1;
                }
            }
            return;
        }
    }
}

var storedTabs = [-1, -1, -1];
var doStore = false;

function storeTab() {
    doStore = !doStore;
}

function tabShortcut(buttonIndex) {
    if (doStore) { // record button was pressed so store this tab
        doStore = false;
        querying = browser.tabs.query({ currentWindow: true, active:true });
        querying.then(function(result){
            if (result.length == 1){
                storedTabs[buttonIndex] = result[0].id;
            }
        });
    } else { // jump to a stored tab (if it exists)
        if (storedTabs[buttonIndex] != -1) {
            var updating = browser.tabs.update(storedTabs[buttonIndex], {
                active: true
            });
        }
    }
}

var port = browser.runtime.connectNative("pypoti");

port.onMessage.addListener((response) => {
    var querying = browser.tabs.query({ currentWindow: true });
    if (response == "left") {
        querying.then(tabLeft, onError);

    } else if (response == "right") {
        querying.then(tabRight, onError);

    } else if (response == "click") {
        querying.then(tabClose, onError);

    } else if (response == "store") {
        querying.then(storeTab(), onError);

    } else if (response == "tab1") {
        querying.then(tabShortcut(0), onError);

    } else if (response == "tab2") {
        querying.then(tabShortcut(1), onError);

    } else if (response == "tab3") {
        querying.then(tabShortcut(2), onError);
    }
});

port.onDisconnect.addListener((p) => {
    if (p.error) {
        console.log(`Disconnected due to an error: ${p.error.message}`);
    }
});


function onError(error) {
    console.log(`Error: ${error}`);
}

function tabLeft(tabs) {
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

var storedTabs = [-1, -1, -1, -1];

function storeTab(buttonIndex) {
    querying = browser.tabs.query({ currentWindow: true, active:true });
    querying.then(function(result){
        if (result.length == 1){
            storedTabs[buttonIndex] = result[0].id;
        }
    });
}

function tabShortcut(buttonIndex) {
    if (storedTabs[buttonIndex] != -1) {
        var updating = browser.tabs.update(storedTabs[buttonIndex], {
            active: true
        });
    }
}

function restoreMostRecentTab() {
  var gettingSessions = browser.sessions.getRecentlyClosed({
    maxResults: 1
  });
  gettingSessions.then(function(sessionInfos){
      if (!sessionInfos.length) {
        console.log("No sessions found")
        return;
      }
      let sessionInfo = sessionInfos[0];
      if (sessionInfo.tab) {
        browser.sessions.restore(sessionInfo.tab.sessionId);
      } else {
        browser.sessions.restore(sessionInfo.window.sessionId);
      }
  }, onError);
}

var port = browser.runtime.connectNative("pypoti");

port.onMessage.addListener((response) => {
    var querying = browser.tabs.query({ currentWindow: true });
    if (response == "left") {
        querying.then(tabLeft, onError);

    } else if (response == "right") {
        querying.then(tabRight, onError);

    } else if (response == "click-short") {
        querying.then(tabClose, onError);

    } else if (response == "click-long") {
        querying.then(restoreMostRecentTab, onError);

    } else if (response == "btn-1-short") {
        querying.then(tabShortcut(0), onError);

    } else if (response == "btn-1-long") {
        querying.then(storeTab(0), onError);

    } else if (response == "btn-2-short") {
        querying.then(tabShortcut(1), onError);

    } else if (response == "btn-2-long") {
        querying.then(storeTab(1), onError);

    } else if (response == "btn-3-short") {
        querying.then(tabShortcut(2), onError);

    } else if (response == "btn-3-long") {
        querying.then(storeTab(2), onError);

    } else if (response == "btn-4-short") {
        querying.then(tabShortcut(3), onError);

    } else if (response == "btn-4-long") {
        querying.then(storeTab(3), onError);
    }
});

port.onDisconnect.addListener((p) => {
    if (p.error) {
        console.log(`Disconnected due to an error: ${p.error.message}`);
    }
});

console.time("mavka");
const bufferScript = document.createElement("script");
bufferScript.src = "https://bundle.run/buffer@6.0.3";
bufferScript.onload = async function() {
  window.Buffer = window.buffer.Buffer;
  const mavkaScripts = document.querySelectorAll("script[type='text/mavka']");

  const codeLines = [];

  for (const mavkaScript of mavkaScripts) {
    const src = mavkaScript.src;
    const text = mavkaScript.textContent;
    if (src) {
      const response = await fetch(src);
      codeLines.push(text, await response.text());
    } else {
      codeLines.push(text);
    }
  }

  const code = codeLines.join("\n").trim();

  if (code) {
    const iframe = document.createElement("iframe");
    iframe.src = "./jj.html#data=" + Buffer.from(JSON.stringify({ code })).toString("base64");
    iframe.style.width = "100%";
    iframe.style.height = "100%";
    iframe.style.border = "none";
    window.addEventListener("message", function(event) {
      if (event.data) {
        try {
          iframe.remove();

          const data = JSON.parse(event.data);

          console.timeEnd("mavka");

          if (data.type === "compilation_result") {
            const mavkaLoader = document.getElementById("mavkaLoader");
            if (mavkaLoader) {
              mavkaLoader.remove();
            }
            if (data.result) {
              if (data.result.error) {
                console.error(data.result.error);
              } else {
                const compiledScript = document.createElement("script");
                compiledScript.textContent = data.result.result;
                document.body.appendChild(compiledScript);
              }
            }
          }
        } catch (e) {
          console.error(e);
        }
      }
    }, false);
    document.body.appendChild(iframe);
  }
};
document.head.appendChild(bufferScript);

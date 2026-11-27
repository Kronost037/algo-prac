
const source=document.querySelector('#code');
if(source){
 document.querySelector('#section').textContent=document.querySelector('#section').textContent.replaceAll('_',' ');
 const key='source:'+location.search;
 if(!source.value)source.value=sessionStorage.getItem(key)||'';
 source.oninput=()=>sessionStorage.setItem(key,source.value);
 document.querySelector('#file').onchange=async e=>{const f=e.target.files[0];if(f&&(!source.value||confirm('Replace the current source?'))){source.value=await f.text();source.oninput();}};
}
const builder=document.querySelector('#builder');
if(builder){for(const field of builder.elements){if(!field.name)continue;field.value=sessionStorage.getItem('builder:'+field.name)||'';field.oninput=()=>sessionStorage.setItem('builder:'+field.name,field.value);}}
for(const form of document.forms)form.onsubmit=()=>{const button=form.querySelector('button[type=submit]');button.disabled=true;button.textContent='Working…';};

for (const box of document.querySelectorAll('#code, textarea[name=solution], textarea[name=generator]')) {
 let escapeTab=false;
 box.addEventListener('keydown',event=>{
  if(event.key==='Escape'){escapeTab=true;return;}
  if(event.key!=='Tab'||escapeTab){escapeTab=false;return;}
  event.preventDefault();
  const value=box.value,start=box.selectionStart,end=box.selectionEnd;
  if(!event.shiftKey && start===end){
   box.setRangeText('    ',start,end,'end');
  }else{
   const first=value.slice(0,start).lastIndexOf('\n')+1;
   const last=end>start && value[end-1]==='\n'?end-1:end;
   const lines=value.slice(first,last).split('\n');
   const indent=line=>event.shiftKey?line.replace(/^( {1,4}|\t)/,''):'    '+line;
   const changed=lines.map(indent).join('\n');
   box.setRangeText(changed,first,last,'preserve');
   const delta=indent(lines[0]).length-lines[0].length;
   box.setSelectionRange(Math.max(first,start+delta),end+changed.length-(last-first));
  }
  box.dispatchEvent(new Event('input',{bubbles:true}));
 });
}
const statement=document.querySelector('#statement');
if(statement){
 const paragraphs=statement.textContent.split(/\n\s*\n/);
 statement.replaceChildren();
 for(const part of paragraphs){
  const lines=part.split('\n');
  if(lines.length>1 && ['Input','Output','Constraints'].includes(lines[0])){
   const heading=document.createElement('h2');heading.textContent=lines.shift();statement.append(heading);
  }
  const p=document.createElement('p');p.textContent=lines.join('\n');statement.append(p);
 }
}
document.querySelector('a[href="#editorial"]')?.addEventListener('click',()=>document.querySelector('#editorial').open=true);

#include "starter.h"

int main (int argc, char *argv[])
{

	int failures=1;

	int oneToOne=0;

	dc= new Controller(8,1024,1024,1024,oneToOne,100000000);
int runFor=100000000;
	dc->instantiateFlow(dc->all_hosts[1],dc->all_hosts[17],10,58368,0.0);
	dc->instantiateFlow(dc->all_hosts[24],dc->all_hosts[31],10,304,3600.0);
	dc->instantiateFlow(dc->all_hosts[23],dc->all_hosts[42],10,539,7200.0);
	dc->instantiateFlow(dc->all_hosts[11],dc->all_hosts[14],10,328704,10800.0);
	dc->instantiateFlow(dc->all_hosts[8],dc->all_hosts[35],10,587776,14400.0);
	dc->instantiateFlow(dc->all_hosts[15],dc->all_hosts[7],10,578560,18000.0);
	dc->instantiateFlow(dc->all_hosts[56],dc->all_hosts[3],10,739328,21600.0);
	dc->instantiateFlow(dc->all_hosts[51],dc->all_hosts[50],10,722944,25200.0);
	dc->instantiateFlow(dc->all_hosts[60],dc->all_hosts[47],10,177,28800.0);
	dc->instantiateFlow(dc->all_hosts[28],dc->all_hosts[60],10,313344,32400.0);
	dc->instantiateFlow(dc->all_hosts[44],dc->all_hosts[8],10,472064,36000.0);
	dc->instantiateFlow(dc->all_hosts[45],dc->all_hosts[23],10,719,39600.0);
	dc->instantiateFlow(dc->all_hosts[38],dc->all_hosts[38],10,480256,43200.0);
	dc->instantiateFlow(dc->all_hosts[7],dc->all_hosts[46],10,165,46800.0);
	dc->instantiateFlow(dc->all_hosts[41],dc->all_hosts[53],10,352256,50400.0);
	dc->instantiateFlow(dc->all_hosts[24],dc->all_hosts[6],10,868,54000.0);
	dc->instantiateFlow(dc->all_hosts[19],dc->all_hosts[13],10,372736,57600.0);
	dc->instantiateFlow(dc->all_hosts[57],dc->all_hosts[43],10,77,61200.0);
	dc->instantiateFlow(dc->all_hosts[40],dc->all_hosts[36],10,897024,64800.0);
	dc->instantiateFlow(dc->all_hosts[58],dc->all_hosts[20],10,122,68400.0);
	dc->instantiateFlow(dc->all_hosts[5],dc->all_hosts[0],10,255,72000.0);
	dc->instantiateFlow(dc->all_hosts[5],dc->all_hosts[37],10,607232,75600.0);
	dc->instantiateFlow(dc->all_hosts[3],dc->all_hosts[41],10,492,79200.0);
	dc->instantiateFlow(dc->all_hosts[57],dc->all_hosts[2],10,69632,82800.0);
	dc->instantiateFlow(dc->all_hosts[6],dc->all_hosts[25],10,685,86400.0);
	dc->instantiateFlow(dc->all_hosts[52],dc->all_hosts[58],10,460,90000.0);
	dc->instantiateFlow(dc->all_hosts[48],dc->all_hosts[25],10,921600,93600.0);
	dc->instantiateFlow(dc->all_hosts[56],dc->all_hosts[25],10,685,97200.0);
	dc->instantiateFlow(dc->all_hosts[21],dc->all_hosts[59],10,326656,100800.0);
	dc->instantiateFlow(dc->all_hosts[49],dc->all_hosts[11],10,418,104400.0);
	dc->instantiateFlow(dc->all_hosts[33],dc->all_hosts[8],10,868352,108000.0);
	dc->instantiateFlow(dc->all_hosts[50],dc->all_hosts[2],10,665600,111600.0);
	dc->instantiateFlow(dc->all_hosts[55],dc->all_hosts[52],10,909312,115200.0);
	dc->instantiateFlow(dc->all_hosts[32],dc->all_hosts[51],10,35840,118800.0);
	dc->instantiateFlow(dc->all_hosts[17],dc->all_hosts[54],10,335872,122400.0);
	dc->instantiateFlow(dc->all_hosts[37],dc->all_hosts[42],10,979968,126000.0);
	dc->instantiateFlow(dc->all_hosts[17],dc->all_hosts[14],10,1020928,129600.0);
	dc->instantiateFlow(dc->all_hosts[30],dc->all_hosts[31],10,606208,133200.0);
	dc->instantiateFlow(dc->all_hosts[13],dc->all_hosts[21],10,49152,136800.0);
	dc->instantiateFlow(dc->all_hosts[28],dc->all_hosts[8],10,142336,140400.0);
	dc->instantiateFlow(dc->all_hosts[50],dc->all_hosts[26],10,429056,144000.0);
	dc->instantiateFlow(dc->all_hosts[35],dc->all_hosts[10],10,943104,147600.0);
	dc->instantiateFlow(dc->all_hosts[49],dc->all_hosts[34],10,178176,151200.0);
	dc->instantiateFlow(dc->all_hosts[20],dc->all_hosts[52],10,53248,154800.0);
	dc->instantiateFlow(dc->all_hosts[43],dc->all_hosts[13],10,999424,158400.0);
	dc->instantiateFlow(dc->all_hosts[34],dc->all_hosts[43],10,915456,162000.0);
	dc->instantiateFlow(dc->all_hosts[13],dc->all_hosts[12],10,692224,165600.0);
	dc->instantiateFlow(dc->all_hosts[41],dc->all_hosts[13],10,324608,169200.0);
	dc->instantiateFlow(dc->all_hosts[56],dc->all_hosts[44],10,76800,172800.0);
	dc->instantiateFlow(dc->all_hosts[18],dc->all_hosts[5],10,143360,176400.0);
	dc->instantiateFlow(dc->all_hosts[60],dc->all_hosts[14],10,820224,180000.0);
	dc->instantiateFlow(dc->all_hosts[29],dc->all_hosts[22],10,197632,183600.0);
	dc->instantiateFlow(dc->all_hosts[1],dc->all_hosts[9],10,391168,187200.0);
	dc->instantiateFlow(dc->all_hosts[49],dc->all_hosts[49],10,999424,190800.0);
	dc->instantiateFlow(dc->all_hosts[5],dc->all_hosts[38],10,229376,194400.0);
	dc->instantiateFlow(dc->all_hosts[8],dc->all_hosts[40],10,969728,198000.0);
	dc->instantiateFlow(dc->all_hosts[29],dc->all_hosts[15],10,645120,201600.0);
	dc->instantiateFlow(dc->all_hosts[47],dc->all_hosts[45],10,634880,205200.0);
	dc->instantiateFlow(dc->all_hosts[21],dc->all_hosts[5],10,456704,208800.0);
	dc->instantiateFlow(dc->all_hosts[27],dc->all_hosts[12],10,903168,212400.0);
	dc->instantiateFlow(dc->all_hosts[7],dc->all_hosts[38],10,860160,216000.0);
	dc->instantiateFlow(dc->all_hosts[57],dc->all_hosts[47],10,64512,219600.0);
	dc->instantiateFlow(dc->all_hosts[41],dc->all_hosts[25],10,291840,223200.0);
	dc->instantiateFlow(dc->all_hosts[23],dc->all_hosts[37],10,242688,226800.0);
	dc->instantiateFlow(dc->all_hosts[54],dc->all_hosts[20],10,740352,230400.0);
	dc->instantiateFlow(dc->all_hosts[6],dc->all_hosts[34],10,434176,234000.0);
	dc->instantiateFlow(dc->all_hosts[28],dc->all_hosts[43],10,431104,237600.0);
	dc->instantiateFlow(dc->all_hosts[25],dc->all_hosts[7],10,603136,241200.0);
	dc->instantiateFlow(dc->all_hosts[60],dc->all_hosts[24],10,861184,244800.0);
	dc->instantiateFlow(dc->all_hosts[17],dc->all_hosts[5],10,15360,248400.0);
	dc->instantiateFlow(dc->all_hosts[19],dc->all_hosts[31],10,629760,252000.0);
	dc->instantiateFlow(dc->all_hosts[49],dc->all_hosts[44],10,501760,255600.0);
	dc->instantiateFlow(dc->all_hosts[9],dc->all_hosts[46],10,513024,259200.0);
	dc->instantiateFlow(dc->all_hosts[58],dc->all_hosts[15],10,744448,262800.0);
	dc->instantiateFlow(dc->all_hosts[23],dc->all_hosts[10],10,607232,266400.0);
	dc->instantiateFlow(dc->all_hosts[15],dc->all_hosts[40],10,421888,270000.0);
	dc->instantiateFlow(dc->all_hosts[19],dc->all_hosts[32],10,629760,273600.0);
	dc->instantiateFlow(dc->all_hosts[51],dc->all_hosts[26],10,382976,277200.0);
	dc->instantiateFlow(dc->all_hosts[54],dc->all_hosts[59],10,946176,280800.0);
	dc->instantiateFlow(dc->all_hosts[2],dc->all_hosts[60],10,1010688,284400.0);
	dc->instantiateFlow(dc->all_hosts[11],dc->all_hosts[5],10,762880,288000.0);
	dc->instantiateFlow(dc->all_hosts[37],dc->all_hosts[22],10,604160,291600.0);
	dc->instantiateFlow(dc->all_hosts[28],dc->all_hosts[7],10,3072,295200.0);
	dc->instantiateFlow(dc->all_hosts[35],dc->all_hosts[16],10,703488,298800.0);
	dc->instantiateFlow(dc->all_hosts[10],dc->all_hosts[54],10,713728,302400.0);
	dc->instantiateFlow(dc->all_hosts[20],dc->all_hosts[2],10,914432,306000.0);
	dc->instantiateFlow(dc->all_hosts[13],dc->all_hosts[48],10,997376,309600.0);
	dc->instantiateFlow(dc->all_hosts[29],dc->all_hosts[25],10,457728,313200.0);
	dc->instantiateFlow(dc->all_hosts[59],dc->all_hosts[11],10,307200,316800.0);
	dc->instantiateFlow(dc->all_hosts[52],dc->all_hosts[11],10,864256,320400.0);
	dc->instantiateFlow(dc->all_hosts[46],dc->all_hosts[59],10,429056,324000.0);
	dc->instantiateFlow(dc->all_hosts[59],dc->all_hosts[37],10,813056,327600.0);
	dc->instantiateFlow(dc->all_hosts[41],dc->all_hosts[54],10,621568,331200.0);
	dc->instantiateFlow(dc->all_hosts[32],dc->all_hosts[19],10,99328,334800.0);
	dc->instantiateFlow(dc->all_hosts[21],dc->all_hosts[30],10,512000,338400.0);
	dc->instantiateFlow(dc->all_hosts[1],dc->all_hosts[0],10,418816,342000.0);
	dc->instantiateFlow(dc->all_hosts[25],dc->all_hosts[5],10,943104,345600.0);
	dc->instantiateFlow(dc->all_hosts[35],dc->all_hosts[20],10,705536,349200.0);
	dc->instantiateFlow(dc->all_hosts[1],dc->all_hosts[54],10,305152,352800.0);
	dc->instantiateFlow(dc->all_hosts[21],dc->all_hosts[46],10,661504,356400.0);
	dc->instantiateFlow(dc->all_hosts[4],dc->all_hosts[43],10,732160,360000.0);
	dc->instantiateFlow(dc->all_hosts[20],dc->all_hosts[21],10,260096,363600.0);
	dc->instantiateFlow(dc->all_hosts[9],dc->all_hosts[2],10,537600,367200.0);
	dc->instantiateFlow(dc->all_hosts[6],dc->all_hosts[25],10,589824,370800.0);
	dc->instantiateFlow(dc->all_hosts[35],dc->all_hosts[59],10,93184,374400.0);
	dc->instantiateFlow(dc->all_hosts[57],dc->all_hosts[21],10,550912,378000.0);
	dc->instantiateFlow(dc->all_hosts[6],dc->all_hosts[29],10,540672,381600.0);
	dc->instantiateFlow(dc->all_hosts[48],dc->all_hosts[6],10,393216,385200.0);
	dc->instantiateFlow(dc->all_hosts[6],dc->all_hosts[51],10,856064,388800.0);
	dc->instantiateFlow(dc->all_hosts[12],dc->all_hosts[9],10,600064,392400.0);
	dc->instantiateFlow(dc->all_hosts[50],dc->all_hosts[53],10,866304,396000.0);
	dc->instantiateFlow(dc->all_hosts[36],dc->all_hosts[54],10,619,399600.0);
	dc->instantiateFlow(dc->all_hosts[56],dc->all_hosts[48],10,232448,403200.0);
	dc->instantiateFlow(dc->all_hosts[60],dc->all_hosts[8],10,852992,406800.0);
	dc->instantiateFlow(dc->all_hosts[32],dc->all_hosts[54],10,1018880,410400.0);
	dc->instantiateFlow(dc->all_hosts[38],dc->all_hosts[23],10,797696,414000.0);
	dc->instantiateFlow(dc->all_hosts[24],dc->all_hosts[4],10,918528,417600.0);
	dc->instantiateFlow(dc->all_hosts[24],dc->all_hosts[5],10,772096,421200.0);
	dc->instantiateFlow(dc->all_hosts[10],dc->all_hosts[45],10,627712,424800.0);
	dc->instantiateFlow(dc->all_hosts[46],dc->all_hosts[49],10,643,428400.0);
	dc->instantiateFlow(dc->all_hosts[31],dc->all_hosts[18],10,730112,432000.0);
	dc->instantiateFlow(dc->all_hosts[58],dc->all_hosts[7],10,340992,435600.0);
	dc->instantiateFlow(dc->all_hosts[50],dc->all_hosts[25],10,314368,439200.0);
	dc->instantiateFlow(dc->all_hosts[35],dc->all_hosts[7],10,444416,442800.0);
	dc->instantiateFlow(dc->all_hosts[39],dc->all_hosts[21],10,803840,446400.0);
	dc->instantiateFlow(dc->all_hosts[45],dc->all_hosts[25],10,376,450000.0);
	dc->instantiateFlow(dc->all_hosts[6],dc->all_hosts[49],10,605184,453600.0);
	dc->instantiateFlow(dc->all_hosts[32],dc->all_hosts[22],10,122880,457200.0);
	dc->instantiateFlow(dc->all_hosts[18],dc->all_hosts[31],10,202752,460800.0);
	dc->instantiateFlow(dc->all_hosts[18],dc->all_hosts[23],10,401408,464400.0);
	dc->instantiateFlow(dc->all_hosts[31],dc->all_hosts[0],10,719872,468000.0);
	dc->instantiateFlow(dc->all_hosts[58],dc->all_hosts[49],10,878,471600.0);
	dc->instantiateFlow(dc->all_hosts[7],dc->all_hosts[4],10,546816,475200.0);
	dc->instantiateFlow(dc->all_hosts[0],dc->all_hosts[26],10,679936,478800.0);
	dc->instantiateFlow(dc->all_hosts[18],dc->all_hosts[21],10,834560,482400.0);
	dc->instantiateFlow(dc->all_hosts[28],dc->all_hosts[8],10,830464,486000.0);
	dc->instantiateFlow(dc->all_hosts[31],dc->all_hosts[41],10,218,489600.0);
	dc->instantiateFlow(dc->all_hosts[57],dc->all_hosts[22],10,632832,493200.0);
	dc->instantiateFlow(dc->all_hosts[16],dc->all_hosts[5],10,261120,496800.0);
	dc->instantiateFlow(dc->all_hosts[59],dc->all_hosts[17],10,793600,500400.0);
	dc->instantiateFlow(dc->all_hosts[25],dc->all_hosts[59],10,442368,504000.0);
	dc->instantiateFlow(dc->all_hosts[57],dc->all_hosts[31],10,659,507600.0);
	dc->instantiateFlow(dc->all_hosts[52],dc->all_hosts[2],10,976896,511200.0);
	dc->instantiateFlow(dc->all_hosts[49],dc->all_hosts[44],10,20480,514800.0);
	dc->instantiateFlow(dc->all_hosts[55],dc->all_hosts[9],10,663,518400.0);
	dc->instantiateFlow(dc->all_hosts[22],dc->all_hosts[54],10,78848,522000.0);
	dc->instantiateFlow(dc->all_hosts[32],dc->all_hosts[46],10,340,525600.0);
	dc->instantiateFlow(dc->all_hosts[44],dc->all_hosts[56],10,780288,529200.0);
	dc->instantiateFlow(dc->all_hosts[48],dc->all_hosts[4],10,596,532800.0);
	dc->instantiateFlow(dc->all_hosts[14],dc->all_hosts[6],10,269312,536400.0);
	dc->instantiateFlow(dc->all_hosts[59],dc->all_hosts[34],10,749,540000.0);
	dc->instantiateFlow(dc->all_hosts[29],dc->all_hosts[41],10,910336,543600.0);
	dc->instantiateFlow(dc->all_hosts[11],dc->all_hosts[22],10,767,547200.0);
	dc->instantiateFlow(dc->all_hosts[58],dc->all_hosts[11],10,907,550800.0);
	dc->instantiateFlow(dc->all_hosts[50],dc->all_hosts[38],10,948224,554400.0);
	dc->instantiateFlow(dc->all_hosts[30],dc->all_hosts[20],10,213,558000.0);
	dc->instantiateFlow(dc->all_hosts[21],dc->all_hosts[45],10,796672,561600.0);
	dc->instantiateFlow(dc->all_hosts[17],dc->all_hosts[42],10,213,565200.0);
	dc->instantiateFlow(dc->all_hosts[32],dc->all_hosts[56],10,557056,568800.0);
	dc->instantiateFlow(dc->all_hosts[6],dc->all_hosts[30],10,847872,572400.0);
	dc->instantiateFlow(dc->all_hosts[19],dc->all_hosts[59],10,713728,576000.0);
	dc->instantiateFlow(dc->all_hosts[45],dc->all_hosts[11],10,398,579600.0);
	dc->instantiateFlow(dc->all_hosts[51],dc->all_hosts[7],10,991232,583200.0);
	dc->instantiateFlow(dc->all_hosts[40],dc->all_hosts[59],10,678,586800.0);
	dc->instantiateFlow(dc->all_hosts[30],dc->all_hosts[32],10,800768,590400.0);
	dc->instantiateFlow(dc->all_hosts[44],dc->all_hosts[42],10,306,594000.0);
	dc->instantiateFlow(dc->all_hosts[6],dc->all_hosts[57],10,818176,597600.0);
	dc->instantiateFlow(dc->all_hosts[38],dc->all_hosts[44],10,368,601200.0);
	dc->instantiateFlow(dc->all_hosts[36],dc->all_hosts[24],10,40960,604800.0);
	dc->instantiateFlow(dc->all_hosts[34],dc->all_hosts[59],10,398336,608400.0);
	dc->instantiateFlow(dc->all_hosts[1],dc->all_hosts[47],10,579584,612000.0);
	dc->instantiateFlow(dc->all_hosts[46],dc->all_hosts[2],10,280576,615600.0);
	dc->instantiateFlow(dc->all_hosts[28],dc->all_hosts[11],10,576512,619200.0);
	dc->instantiateFlow(dc->all_hosts[40],dc->all_hosts[53],10,534,622800.0);
	dc->instantiateFlow(dc->all_hosts[46],dc->all_hosts[1],10,233472,626400.0);
	dc->instantiateFlow(dc->all_hosts[30],dc->all_hosts[45],10,419,630000.0);
	dc->instantiateFlow(dc->all_hosts[10],dc->all_hosts[18],10,889856,633600.0);
	dc->instantiateFlow(dc->all_hosts[15],dc->all_hosts[22],10,470,637200.0);
	dc->instantiateFlow(dc->all_hosts[3],dc->all_hosts[60],10,809984,640800.0);
	dc->instantiateFlow(dc->all_hosts[11],dc->all_hosts[11],10,201,644400.0);
	dc->instantiateFlow(dc->all_hosts[58],dc->all_hosts[35],10,101376,648000.0);
	dc->instantiateFlow(dc->all_hosts[39],dc->all_hosts[20],10,387072,651600.0);
	dc->instantiateFlow(dc->all_hosts[47],dc->all_hosts[39],10,567296,655200.0);
	dc->instantiateFlow(dc->all_hosts[55],dc->all_hosts[52],10,266240,658800.0);
	dc->instantiateFlow(dc->all_hosts[30],dc->all_hosts[19],10,594944,662400.0);
	dc->instantiateFlow(dc->all_hosts[11],dc->all_hosts[59],10,779,666000.0);
	dc->instantiateFlow(dc->all_hosts[52],dc->all_hosts[2],10,370688,669600.0);
	dc->instantiateFlow(dc->all_hosts[55],dc->all_hosts[36],10,993,673200.0);
	dc->instantiateFlow(dc->all_hosts[52],dc->all_hosts[59],10,325632,676800.0);
	dc->instantiateFlow(dc->all_hosts[0],dc->all_hosts[44],10,812032,680400.0);
	dc->instantiateFlow(dc->all_hosts[23],dc->all_hosts[37],10,306,684000.0);
	dc->instantiateFlow(dc->all_hosts[0],dc->all_hosts[17],10,43008,687600.0);
	dc->instantiateFlow(dc->all_hosts[59],dc->all_hosts[50],10,862,691200.0);
	dc->instantiateFlow(dc->all_hosts[59],dc->all_hosts[17],10,774144,694800.0);
	dc->instantiateFlow(dc->all_hosts[37],dc->all_hosts[33],10,460800,698400.0);
	dc->instantiateFlow(dc->all_hosts[6],dc->all_hosts[17],10,5,702000.0);
	dc->instantiateFlow(dc->all_hosts[31],dc->all_hosts[55],10,696320,705600.0);
	dc->instantiateFlow(dc->all_hosts[31],dc->all_hosts[59],10,515,709200.0);
	dc->instantiateFlow(dc->all_hosts[52],dc->all_hosts[0],10,251904,712800.0);
	dc->instantiateFlow(dc->all_hosts[49],dc->all_hosts[21],10,887808,716400.0);
	dc->instantiateFlow(dc->all_hosts[2],dc->all_hosts[23],10,321536,720000.0);
	dc->instantiateFlow(dc->all_hosts[11],dc->all_hosts[16],10,430080,723600.0);
	dc->instantiateFlow(dc->all_hosts[6],dc->all_hosts[44],10,375808,727200.0);
	dc->instantiateFlow(dc->all_hosts[25],dc->all_hosts[27],10,977920,730800.0);
	dc->instantiateFlow(dc->all_hosts[56],dc->all_hosts[34],10,914,734400.0);
	dc->instantiateFlow(dc->all_hosts[7],dc->all_hosts[58],10,901120,738000.0);
	dc->instantiateFlow(dc->all_hosts[27],dc->all_hosts[55],10,59,741600.0);
	dc->instantiateFlow(dc->all_hosts[51],dc->all_hosts[37],10,118784,745200.0);
	dc->instantiateFlow(dc->all_hosts[27],dc->all_hosts[13],10,551936,748800.0);
	dc->instantiateFlow(dc->all_hosts[4],dc->all_hosts[39],10,346,752400.0);
	dc->instantiateFlow(dc->all_hosts[11],dc->all_hosts[26],10,299008,756000.0);
	dc->instantiateFlow(dc->all_hosts[27],dc->all_hosts[60],10,704,759600.0);
	dc->instantiateFlow(dc->all_hosts[56],dc->all_hosts[22],10,351232,763200.0);
	dc->instantiateFlow(dc->all_hosts[55],dc->all_hosts[17],10,882,766800.0);
	dc->instantiateFlow(dc->all_hosts[24],dc->all_hosts[40],10,403456,770400.0);
	dc->instantiateFlow(dc->all_hosts[8],dc->all_hosts[26],10,294,774000.0);
	dc->instantiateFlow(dc->all_hosts[7],dc->all_hosts[16],10,629760,777600.0);
	dc->instantiateFlow(dc->all_hosts[13],dc->all_hosts[9],10,36,781200.0);
	dc->instantiateFlow(dc->all_hosts[43],dc->all_hosts[52],10,984064,784800.0);
	dc->instantiateFlow(dc->all_hosts[50],dc->all_hosts[58],10,566272,788400.0);
	dc->instantiateFlow(dc->all_hosts[49],dc->all_hosts[27],10,114688,792000.0);
	dc->instantiateFlow(dc->all_hosts[53],dc->all_hosts[53],10,917,795600.0);
	dc->instantiateFlow(dc->all_hosts[46],dc->all_hosts[25],10,217,799200.0);
	dc->instantiateFlow(dc->all_hosts[3],dc->all_hosts[42],10,969,802800.0);
	dc->instantiateFlow(dc->all_hosts[2],dc->all_hosts[22],10,464896,806400.0);
	dc->instantiateFlow(dc->all_hosts[35],dc->all_hosts[34],10,338,810000.0);
	dc->instantiateFlow(dc->all_hosts[12],dc->all_hosts[34],10,348160,813600.0);
	dc->instantiateFlow(dc->all_hosts[6],dc->all_hosts[32],10,669696,817200.0);
	dc->instantiateFlow(dc->all_hosts[60],dc->all_hosts[47],10,956416,820800.0);
	dc->instantiateFlow(dc->all_hosts[46],dc->all_hosts[47],10,372736,824400.0);
	dc->instantiateFlow(dc->all_hosts[0],dc->all_hosts[26],10,324608,828000.0);
	dc->instantiateFlow(dc->all_hosts[5],dc->all_hosts[2],10,94208,831600.0);
	dc->instantiateFlow(dc->all_hosts[51],dc->all_hosts[20],10,713728,835200.0);
	dc->instantiateFlow(dc->all_hosts[24],dc->all_hosts[57],10,573440,838800.0);
	dc->instantiateFlow(dc->all_hosts[56],dc->all_hosts[57],10,240640,842400.0);
	dc->instantiateFlow(dc->all_hosts[54],dc->all_hosts[30],10,795648,846000.0);
	dc->instantiateFlow(dc->all_hosts[56],dc->all_hosts[14],10,497664,849600.0);
	dc->instantiateFlow(dc->all_hosts[1],dc->all_hosts[10],10,522240,853200.0);
	dc->instantiateFlow(dc->all_hosts[7],dc->all_hosts[9],10,821248,856800.0);
	dc->instantiateFlow(dc->all_hosts[9],dc->all_hosts[42],10,272384,860400.0);
	dc->instantiateFlow(dc->all_hosts[37],dc->all_hosts[35],10,43008,864000.0);
	dc->instantiateFlow(dc->all_hosts[4],dc->all_hosts[2],10,473088,867600.0);
	dc->instantiateFlow(dc->all_hosts[3],dc->all_hosts[7],10,756736,871200.0);
	dc->instantiateFlow(dc->all_hosts[9],dc->all_hosts[20],10,771072,874800.0);
	dc->instantiateFlow(dc->all_hosts[52],dc->all_hosts[24],10,825344,878400.0);
	dc->instantiateFlow(dc->all_hosts[43],dc->all_hosts[26],10,370688,882000.0);
	dc->instantiateFlow(dc->all_hosts[26],dc->all_hosts[57],10,436224,885600.0);
	dc->instantiateFlow(dc->all_hosts[21],dc->all_hosts[5],10,444416,889200.0);
	dc->instantiateFlow(dc->all_hosts[44],dc->all_hosts[35],10,388096,892800.0);
	dc->instantiateFlow(dc->all_hosts[1],dc->all_hosts[6],10,972800,896400.0);
	dc->instantiateFlow(dc->all_hosts[49],dc->all_hosts[43],10,1013760,900000.0);
	dc->instantiateFlow(dc->all_hosts[15],dc->all_hosts[39],10,463872,903600.0);
	dc->instantiateFlow(dc->all_hosts[45],dc->all_hosts[42],10,972800,907200.0);
	dc->instantiateFlow(dc->all_hosts[28],dc->all_hosts[43],10,410624,910800.0);
	dc->instantiateFlow(dc->all_hosts[48],dc->all_hosts[58],10,564224,914400.0);
	dc->instantiateFlow(dc->all_hosts[34],dc->all_hosts[0],10,1015808,918000.0);
	dc->instantiateFlow(dc->all_hosts[60],dc->all_hosts[31],10,936960,921600.0);
	dc->instantiateFlow(dc->all_hosts[45],dc->all_hosts[20],10,393216,925200.0);
	dc->instantiateFlow(dc->all_hosts[46],dc->all_hosts[7],10,244736,928800.0);
	dc->instantiateFlow(dc->all_hosts[11],dc->all_hosts[49],10,948224,932400.0);
	dc->instantiateFlow(dc->all_hosts[36],dc->all_hosts[30],10,958464,936000.0);
	dc->instantiateFlow(dc->all_hosts[12],dc->all_hosts[51],10,858112,939600.0);
	dc->instantiateFlow(dc->all_hosts[46],dc->all_hosts[28],10,708608,943200.0);
	dc->instantiateFlow(dc->all_hosts[31],dc->all_hosts[35],10,921600,946800.0);
	dc->instantiateFlow(dc->all_hosts[17],dc->all_hosts[35],10,89088,950400.0);
	dc->instantiateFlow(dc->all_hosts[43],dc->all_hosts[55],10,961536,954000.0);
	dc->instantiateFlow(dc->all_hosts[48],dc->all_hosts[8],10,560128,957600.0);
	dc->instantiateFlow(dc->all_hosts[15],dc->all_hosts[17],10,89088,961200.0);
	dc->instantiateFlow(dc->all_hosts[54],dc->all_hosts[41],10,439296,964800.0);
	dc->instantiateFlow(dc->all_hosts[53],dc->all_hosts[48],10,33792,968400.0);
	dc->instantiateFlow(dc->all_hosts[48],dc->all_hosts[33],10,220160,972000.0);
	dc->instantiateFlow(dc->all_hosts[55],dc->all_hosts[13],10,867328,975600.0);
	dc->instantiateFlow(dc->all_hosts[32],dc->all_hosts[24],10,921600,979200.0);
	dc->instantiateFlow(dc->all_hosts[46],dc->all_hosts[20],10,60416,982800.0);
	dc->instantiateFlow(dc->all_hosts[60],dc->all_hosts[38],10,599040,986400.0);
	dc->instantiateFlow(dc->all_hosts[2],dc->all_hosts[21],10,579584,990000.0);
	dc->instantiateFlow(dc->all_hosts[56],dc->all_hosts[14],10,829440,993600.0);
	dc->instantiateFlow(dc->all_hosts[38],dc->all_hosts[47],10,460800,997200.0);
	dc->instantiateFlow(dc->all_hosts[0],dc->all_hosts[33],10,400384,1000800.0);
	dc->instantiateFlow(dc->all_hosts[52],dc->all_hosts[50],10,9216,1004400.0);
	dc->instantiateFlow(dc->all_hosts[7],dc->all_hosts[5],10,635904,1008000.0);
	dc->instantiateFlow(dc->all_hosts[55],dc->all_hosts[0],10,660480,1011600.0);
	dc->instantiateFlow(dc->all_hosts[54],dc->all_hosts[60],10,700416,1015200.0);
	dc->instantiateFlow(dc->all_hosts[14],dc->all_hosts[45],10,844800,1018800.0);
	dc->instantiateFlow(dc->all_hosts[58],dc->all_hosts[60],10,769024,1022400.0);
	dc->instantiateFlow(dc->all_hosts[57],dc->all_hosts[18],10,809984,1026000.0);
	dc->instantiateFlow(dc->all_hosts[29],dc->all_hosts[3],10,649216,1029600.0);
	dc->instantiateFlow(dc->all_hosts[22],dc->all_hosts[48],10,467968,1033200.0);
	dc->instantiateFlow(dc->all_hosts[32],dc->all_hosts[31],10,60416,1036800.0);
	dc->instantiateFlow(dc->all_hosts[30],dc->all_hosts[21],10,253952,1040400.0);
	dc->instantiateFlow(dc->all_hosts[17],dc->all_hosts[4],10,949248,1044000.0);
	dc->instantiateFlow(dc->all_hosts[29],dc->all_hosts[50],10,943104,1047600.0);
	dc->instantiateFlow(dc->all_hosts[31],dc->all_hosts[46],10,631808,1051200.0);
	dc->instantiateFlow(dc->all_hosts[60],dc->all_hosts[19],10,123904,1054800.0);
	dc->instantiateFlow(dc->all_hosts[12],dc->all_hosts[10],10,526336,1058400.0);
	dc->instantiateFlow(dc->all_hosts[54],dc->all_hosts[0],10,681984,1062000.0);
	dc->instantiateFlow(dc->all_hosts[52],dc->all_hosts[53],10,969728,1065600.0);
	dc->instantiateFlow(dc->all_hosts[45],dc->all_hosts[42],10,634880,1069200.0);
	dc->instantiateFlow(dc->all_hosts[50],dc->all_hosts[10],10,823296,1072800.0);
	dc->instantiateFlow(dc->all_hosts[15],dc->all_hosts[55],10,93184,1076400.0);
	dc->instantiateFlow(dc->all_hosts[57],dc->all_hosts[60],10,978944,1080000.0);
	dc->instantiateFlow(dc->all_hosts[45],dc->all_hosts[53],10,26624,1083600.0);
	dc->instantiateFlow(dc->all_hosts[31],dc->all_hosts[28],10,52224,1087200.0);
	dc->instantiateFlow(dc->all_hosts[31],dc->all_hosts[49],10,890880,1090800.0);
	dc->instantiateFlow(dc->all_hosts[10],dc->all_hosts[30],10,1010688,1094400.0);
	dc->instantiateFlow(dc->all_hosts[56],dc->all_hosts[14],10,23552,1098000.0);
	dc->instantiateFlow(dc->all_hosts[11],dc->all_hosts[30],10,676864,1101600.0);
	dc->instantiateFlow(dc->all_hosts[44],dc->all_hosts[5],10,124928,1105200.0);
	dc->instantiateFlow(dc->all_hosts[34],dc->all_hosts[13],10,573440,1108800.0);
	dc->instantiateFlow(dc->all_hosts[31],dc->all_hosts[25],10,282624,1112400.0);
	dc->instantiateFlow(dc->all_hosts[2],dc->all_hosts[49],10,458752,1116000.0);
	dc->instantiateFlow(dc->all_hosts[22],dc->all_hosts[35],10,272384,1119600.0);
	dc->instantiateFlow(dc->all_hosts[25],dc->all_hosts[21],10,342016,1123200.0);
	dc->instantiateFlow(dc->all_hosts[24],dc->all_hosts[12],10,689152,1126800.0);
	dc->instantiateFlow(dc->all_hosts[35],dc->all_hosts[2],10,781312,1130400.0);
	dc->instantiateFlow(dc->all_hosts[30],dc->all_hosts[8],10,737280,1134000.0);
	dc->instantiateFlow(dc->all_hosts[18],dc->all_hosts[23],10,461824,1137600.0);
	dc->instantiateFlow(dc->all_hosts[4],dc->all_hosts[5],10,715776,1141200.0);
	dc->instantiateFlow(dc->all_hosts[23],dc->all_hosts[36],10,656384,1144800.0);
	dc->instantiateFlow(dc->all_hosts[15],dc->all_hosts[14],10,146432,1148400.0);
	dc->instantiateFlow(dc->all_hosts[22],dc->all_hosts[41],10,389120,1152000.0);
	dc->instantiateFlow(dc->all_hosts[39],dc->all_hosts[24],10,215040,1155600.0);
	dc->instantiateFlow(dc->all_hosts[10],dc->all_hosts[40],10,495616,1159200.0);
	dc->instantiateFlow(dc->all_hosts[35],dc->all_hosts[43],10,65536,1162800.0);
	dc->instantiateFlow(dc->all_hosts[31],dc->all_hosts[19],10,967680,1166400.0);
	dc->instantiateFlow(dc->all_hosts[37],dc->all_hosts[45],10,38912,1170000.0);
	dc->instantiateFlow(dc->all_hosts[55],dc->all_hosts[50],10,223232,1173600.0);
	dc->instantiateFlow(dc->all_hosts[18],dc->all_hosts[54],10,400384,1177200.0);
	dc->instantiateFlow(dc->all_hosts[39],dc->all_hosts[17],10,138240,1180800.0);
	dc->instantiateFlow(dc->all_hosts[56],dc->all_hosts[26],10,856064,1184400.0);
	dc->instantiateFlow(dc->all_hosts[36],dc->all_hosts[3],10,771072,1188000.0);
	dc->instantiateFlow(dc->all_hosts[5],dc->all_hosts[34],10,732160,1191600.0);
	dc->instantiateFlow(dc->all_hosts[48],dc->all_hosts[38],10,622592,1195200.0);
	dc->instantiateFlow(dc->all_hosts[43],dc->all_hosts[42],10,111616,1198800.0);
	dc->instantiateFlow(dc->all_hosts[16],dc->all_hosts[9],10,164864,1202400.0);
	dc->instantiateFlow(dc->all_hosts[58],dc->all_hosts[7],10,620544,1206000.0);
	dc->instantiateFlow(dc->all_hosts[28],dc->all_hosts[44],10,450560,1209600.0);
	dc->instantiateFlow(dc->all_hosts[46],dc->all_hosts[34],10,246784,1213200.0);
	dc->instantiateFlow(dc->all_hosts[54],dc->all_hosts[31],10,283648,1216800.0);
	dc->instantiateFlow(dc->all_hosts[56],dc->all_hosts[38],10,867328,1220400.0);
	dc->instantiateFlow(dc->all_hosts[47],dc->all_hosts[25],10,405504,1224000.0);
	dc->instantiateFlow(dc->all_hosts[18],dc->all_hosts[4],10,88064,1227600.0);
	dc->instantiateFlow(dc->all_hosts[11],dc->all_hosts[36],10,460800,1231200.0);
	dc->instantiateFlow(dc->all_hosts[49],dc->all_hosts[31],10,816128,1234800.0);
	dc->instantiateFlow(dc->all_hosts[4],dc->all_hosts[40],10,588800,1238400.0);
	dc->instantiateFlow(dc->all_hosts[13],dc->all_hosts[50],10,867328,1242000.0);
	dc->instantiateFlow(dc->all_hosts[39],dc->all_hosts[51],10,332800,1245600.0);
	dc->instantiateFlow(dc->all_hosts[3],dc->all_hosts[27],10,419840,1249200.0);
	dc->instantiateFlow(dc->all_hosts[54],dc->all_hosts[17],10,753664,1252800.0);
	dc->instantiateFlow(dc->all_hosts[28],dc->all_hosts[23],10,374784,1256400.0);
	dc->instantiateFlow(dc->all_hosts[38],dc->all_hosts[22],10,59392,1260000.0);
	dc->instantiateFlow(dc->all_hosts[34],dc->all_hosts[45],10,715776,1263600.0);
	dc->instantiateFlow(dc->all_hosts[2],dc->all_hosts[29],10,798720,1267200.0);
	dc->instantiateFlow(dc->all_hosts[45],dc->all_hosts[55],10,518144,1270800.0);
	dc->instantiateFlow(dc->all_hosts[55],dc->all_hosts[45],10,365568,1274400.0);
	dc->instantiateFlow(dc->all_hosts[53],dc->all_hosts[2],10,753664,1278000.0);
	dc->instantiateFlow(dc->all_hosts[57],dc->all_hosts[6],10,927744,1281600.0);
	dc->instantiateFlow(dc->all_hosts[57],dc->all_hosts[16],10,635904,1285200.0);
	dc->instantiateFlow(dc->all_hosts[24],dc->all_hosts[28],10,854016,1288800.0);
	dc->instantiateFlow(dc->all_hosts[12],dc->all_hosts[46],10,953344,1292400.0);
	dc->instantiateFlow(dc->all_hosts[31],dc->all_hosts[11],10,261120,1296000.0);
	dc->instantiateFlow(dc->all_hosts[5],dc->all_hosts[51],10,114688,1299600.0);
	dc->instantiateFlow(dc->all_hosts[37],dc->all_hosts[7],10,94208,1303200.0);
	dc->instantiateFlow(dc->all_hosts[41],dc->all_hosts[4],10,857088,1306800.0);
	dc->instantiateFlow(dc->all_hosts[7],dc->all_hosts[39],10,15360,1310400.0);
	dc->instantiateFlow(dc->all_hosts[26],dc->all_hosts[48],10,94208,1314000.0);
	dc->instantiateFlow(dc->all_hosts[7],dc->all_hosts[56],10,974848,1317600.0);
	dc->instantiateFlow(dc->all_hosts[33],dc->all_hosts[14],10,707584,1321200.0);
	dc->instantiateFlow(dc->all_hosts[21],dc->all_hosts[42],10,947200,1324800.0);
	dc->instantiateFlow(dc->all_hosts[37],dc->all_hosts[3],10,402432,1328400.0);
	dc->instantiateFlow(dc->all_hosts[29],dc->all_hosts[27],10,760832,1332000.0);
	dc->instantiateFlow(dc->all_hosts[40],dc->all_hosts[38],10,904192,1335600.0);
	dc->instantiateFlow(dc->all_hosts[15],dc->all_hosts[18],10,485376,1339200.0);
	dc->instantiateFlow(dc->all_hosts[9],dc->all_hosts[15],10,246784,1342800.0);
	dc->instantiateFlow(dc->all_hosts[60],dc->all_hosts[17],10,539648,1346400.0);
	dc->instantiateFlow(dc->all_hosts[4],dc->all_hosts[58],10,968704,1350000.0);
	dc->instantiateFlow(dc->all_hosts[53],dc->all_hosts[58],10,716800,1353600.0);
	dc->instantiateFlow(dc->all_hosts[23],dc->all_hosts[20],10,215040,1357200.0);
	dc->instantiateFlow(dc->all_hosts[44],dc->all_hosts[26],10,750592,1360800.0);
	dc->instantiateFlow(dc->all_hosts[30],dc->all_hosts[33],10,500736,1364400.0);
	dc->instantiateFlow(dc->all_hosts[5],dc->all_hosts[56],10,830464,1368000.0);
	dc->instantiateFlow(dc->all_hosts[5],dc->all_hosts[35],10,852992,1371600.0);
	dc->instantiateFlow(dc->all_hosts[1],dc->all_hosts[0],10,768000,1375200.0);
	dc->instantiateFlow(dc->all_hosts[53],dc->all_hosts[19],10,751616,1378800.0);
	dc->instantiateFlow(dc->all_hosts[15],dc->all_hosts[24],10,28672,1382400.0);
	dc->instantiateFlow(dc->all_hosts[16],dc->all_hosts[23],10,1020928,1386000.0);
	dc->instantiateFlow(dc->all_hosts[53],dc->all_hosts[34],10,171008,1389600.0);
	dc->instantiateFlow(dc->all_hosts[36],dc->all_hosts[10],10,686080,1393200.0);
	dc->instantiateFlow(dc->all_hosts[29],dc->all_hosts[44],10,315392,1396800.0);
	dc->instantiateFlow(dc->all_hosts[60],dc->all_hosts[52],10,331776,1400400.0);
	dc->instantiateFlow(dc->all_hosts[53],dc->all_hosts[33],10,729088,1404000.0);
	dc->instantiateFlow(dc->all_hosts[39],dc->all_hosts[34],10,1006592,1407600.0);
	dc->instantiateFlow(dc->all_hosts[54],dc->all_hosts[38],10,368640,1411200.0);
	dc->instantiateFlow(dc->all_hosts[29],dc->all_hosts[2],10,51200,1414800.0);
	dc->instantiateFlow(dc->all_hosts[58],dc->all_hosts[39],10,817152,1418400.0);
	dc->instantiateFlow(dc->all_hosts[52],dc->all_hosts[25],10,945152,1422000.0);
	dc->instantiateFlow(dc->all_hosts[15],dc->all_hosts[41],10,878592,1425600.0);
	dc->instantiateFlow(dc->all_hosts[53],dc->all_hosts[15],10,31744,1429200.0);
	dc->instantiateFlow(dc->all_hosts[4],dc->all_hosts[2],10,166912,1432800.0);
	dc->instantiateFlow(dc->all_hosts[7],dc->all_hosts[25],10,30720,1436400.0);
	dc->instantiateFlow(dc->all_hosts[33],dc->all_hosts[38],10,729088,1440000.0);
	dc->instantiateFlow(dc->all_hosts[45],dc->all_hosts[53],10,517120,1443600.0);
	dc->instantiateFlow(dc->all_hosts[6],dc->all_hosts[50],10,988160,1447200.0);
	dc->instantiateFlow(dc->all_hosts[46],dc->all_hosts[24],10,169984,1450800.0);
	dc->instantiateFlow(dc->all_hosts[25],dc->all_hosts[60],10,591872,1454400.0);
	dc->instantiateFlow(dc->all_hosts[56],dc->all_hosts[20],10,856064,1458000.0);
	dc->instantiateFlow(dc->all_hosts[42],dc->all_hosts[45],10,473088,1461600.0);
	dc->instantiateFlow(dc->all_hosts[24],dc->all_hosts[8],10,115712,1465200.0);
	dc->instantiateFlow(dc->all_hosts[41],dc->all_hosts[41],10,199680,1468800.0);
	dc->instantiateFlow(dc->all_hosts[43],dc->all_hosts[11],10,236544,1472400.0);
	dc->instantiateFlow(dc->all_hosts[31],dc->all_hosts[55],10,256000,1476000.0);
	dc->instantiateFlow(dc->all_hosts[24],dc->all_hosts[51],10,714752,1479600.0);
	dc->instantiateFlow(dc->all_hosts[52],dc->all_hosts[42],10,551936,1483200.0);
	dc->instantiateFlow(dc->all_hosts[8],dc->all_hosts[35],10,694272,1486800.0);
	dc->instantiateFlow(dc->all_hosts[45],dc->all_hosts[55],10,464896,1490400.0);
	dc->instantiateFlow(dc->all_hosts[30],dc->all_hosts[51],10,39936,1494000.0);
	dc->instantiateFlow(dc->all_hosts[24],dc->all_hosts[1],10,520192,1497600.0);
	dc->instantiateFlow(dc->all_hosts[21],dc->all_hosts[0],10,1009664,1501200.0);
	dc->instantiateFlow(dc->all_hosts[56],dc->all_hosts[40],10,428032,1504800.0);
	dc->instantiateFlow(dc->all_hosts[29],dc->all_hosts[3],10,434176,1508400.0);
	dc->instantiateFlow(dc->all_hosts[1],dc->all_hosts[22],10,577536,1512000.0);
	dc->instantiateFlow(dc->all_hosts[48],dc->all_hosts[52],10,542720,1515600.0);
	dc->instantiateFlow(dc->all_hosts[38],dc->all_hosts[35],10,30720,1519200.0);
	dc->instantiateFlow(dc->all_hosts[1],dc->all_hosts[42],10,772096,1522800.0);
	dc->instantiateFlow(dc->all_hosts[6],dc->all_hosts[12],10,572416,1526400.0);
	dc->instantiateFlow(dc->all_hosts[19],dc->all_hosts[19],10,937984,1530000.0);
	dc->instantiateFlow(dc->all_hosts[0],dc->all_hosts[18],10,750592,1533600.0);
	dc->instantiateFlow(dc->all_hosts[12],dc->all_hosts[13],10,937984,1537200.0);
	dc->instantiateFlow(dc->all_hosts[48],dc->all_hosts[44],10,334848,1540800.0);
	dc->instantiateFlow(dc->all_hosts[14],dc->all_hosts[5],10,228352,1544400.0);
	dc->instantiateFlow(dc->all_hosts[2],dc->all_hosts[4],10,27648,1548000.0);
	dc->instantiateFlow(dc->all_hosts[34],dc->all_hosts[13],10,816128,1551600.0);
	dc->instantiateFlow(dc->all_hosts[53],dc->all_hosts[45],10,238592,1555200.0);
	dc->instantiateFlow(dc->all_hosts[42],dc->all_hosts[21],10,857088,1558800.0);
	dc->instantiateFlow(dc->all_hosts[43],dc->all_hosts[58],10,701440,1562400.0);
	dc->instantiateFlow(dc->all_hosts[43],dc->all_hosts[44],10,152576,1566000.0);
	dc->instantiateFlow(dc->all_hosts[19],dc->all_hosts[22],10,497664,1569600.0);
	dc->instantiateFlow(dc->all_hosts[14],dc->all_hosts[40],10,227328,1573200.0);
	dc->instantiateFlow(dc->all_hosts[43],dc->all_hosts[26],10,364544,1576800.0);
	dc->instantiateFlow(dc->all_hosts[5],dc->all_hosts[26],10,23552,1580400.0);
	dc->instantiateFlow(dc->all_hosts[54],dc->all_hosts[56],10,384000,1584000.0);
	dc->instantiateFlow(dc->all_hosts[50],dc->all_hosts[39],10,807936,1587600.0);
	dc->instantiateFlow(dc->all_hosts[9],dc->all_hosts[16],10,887808,1591200.0);
	dc->instantiateFlow(dc->all_hosts[43],dc->all_hosts[46],10,508928,1594800.0);
	dc->instantiateFlow(dc->all_hosts[20],dc->all_hosts[9],10,617472,1598400.0);
	dc->instantiateFlow(dc->all_hosts[35],dc->all_hosts[55],10,863232,1602000.0);
	dc->instantiateFlow(dc->all_hosts[13],dc->all_hosts[20],10,62464,1605600.0);
	dc->instantiateFlow(dc->all_hosts[38],dc->all_hosts[60],10,1014784,1609200.0);
	dc->instantiateFlow(dc->all_hosts[54],dc->all_hosts[50],10,877568,1612800.0);
	dc->instantiateFlow(dc->all_hosts[40],dc->all_hosts[25],10,626688,1616400.0);
	dc->instantiateFlow(dc->all_hosts[8],dc->all_hosts[49],10,816128,1620000.0);
	dc->instantiateFlow(dc->all_hosts[23],dc->all_hosts[32],10,486400,1623600.0);
	dc->instantiateFlow(dc->all_hosts[53],dc->all_hosts[40],10,713728,1627200.0);
	dc->instantiateFlow(dc->all_hosts[43],dc->all_hosts[33],10,505856,1630800.0);
	dc->instantiateFlow(dc->all_hosts[38],dc->all_hosts[35],10,643072,1634400.0);
	dc->instantiateFlow(dc->all_hosts[26],dc->all_hosts[14],10,892928,1638000.0);
	dc->instantiateFlow(dc->all_hosts[13],dc->all_hosts[13],10,68608,1641600.0);
	dc->instantiateFlow(dc->all_hosts[27],dc->all_hosts[36],10,647168,1645200.0);
	dc->instantiateFlow(dc->all_hosts[35],dc->all_hosts[60],10,1009664,1648800.0);
	dc->instantiateFlow(dc->all_hosts[56],dc->all_hosts[10],10,800768,1652400.0);
	dc->instantiateFlow(dc->all_hosts[15],dc->all_hosts[5],10,37888,1656000.0);
	dc->instantiateFlow(dc->all_hosts[12],dc->all_hosts[59],10,465920,1659600.0);
	dc->instantiateFlow(dc->all_hosts[30],dc->all_hosts[18],10,475136,1663200.0);
	dc->instantiateFlow(dc->all_hosts[33],dc->all_hosts[11],10,52224,1666800.0);
	dc->instantiateFlow(dc->all_hosts[26],dc->all_hosts[12],10,984064,1670400.0);
	dc->instantiateFlow(dc->all_hosts[48],dc->all_hosts[0],10,842752,1674000.0);
	dc->instantiateFlow(dc->all_hosts[57],dc->all_hosts[28],10,521216,1677600.0);
	dc->instantiateFlow(dc->all_hosts[52],dc->all_hosts[3],10,904192,1681200.0);
	dc->instantiateFlow(dc->all_hosts[46],dc->all_hosts[20],10,829440,1684800.0);
	dc->instantiateFlow(dc->all_hosts[29],dc->all_hosts[41],10,834560,1688400.0);
	dc->instantiateFlow(dc->all_hosts[28],dc->all_hosts[26],10,493568,1692000.0);
	dc->instantiateFlow(dc->all_hosts[24],dc->all_hosts[34],10,495616,1695600.0);
	dc->instantiateFlow(dc->all_hosts[18],dc->all_hosts[43],10,197632,1699200.0);
	dc->instantiateFlow(dc->all_hosts[23],dc->all_hosts[9],10,872448,1702800.0);
	dc->instantiateFlow(dc->all_hosts[38],dc->all_hosts[47],10,732160,1706400.0);
	dc->instantiateFlow(dc->all_hosts[17],dc->all_hosts[17],10,658432,1710000.0);
	dc->instantiateFlow(dc->all_hosts[47],dc->all_hosts[57],10,106496,1713600.0);
	dc->instantiateFlow(dc->all_hosts[27],dc->all_hosts[10],10,352256,1717200.0);
	dc->instantiateFlow(dc->all_hosts[43],dc->all_hosts[57],10,594944,1720800.0);
	dc->instantiateFlow(dc->all_hosts[1],dc->all_hosts[18],10,594944,1724400.0);
	dc->instantiateFlow(dc->all_hosts[12],dc->all_hosts[50],10,770048,1728000.0);
	dc->instantiateFlow(dc->all_hosts[31],dc->all_hosts[9],10,862208,1731600.0);
	dc->instantiateFlow(dc->all_hosts[47],dc->all_hosts[26],10,445440,1735200.0);
	dc->instantiateFlow(dc->all_hosts[14],dc->all_hosts[43],10,285696,1738800.0);
	dc->instantiateFlow(dc->all_hosts[6],dc->all_hosts[39],10,601088,1742400.0);
	dc->instantiateFlow(dc->all_hosts[35],dc->all_hosts[13],10,389120,1746000.0);
	dc->instantiateFlow(dc->all_hosts[47],dc->all_hosts[46],10,922624,1749600.0);
	dc->instantiateFlow(dc->all_hosts[38],dc->all_hosts[28],10,581632,1753200.0);
	dc->instantiateFlow(dc->all_hosts[38],dc->all_hosts[55],10,284672,1756800.0);
	dc->instantiateFlow(dc->all_hosts[35],dc->all_hosts[52],10,788480,1760400.0);
	dc->instantiateFlow(dc->all_hosts[35],dc->all_hosts[14],10,605184,1764000.0);
	dc->instantiateFlow(dc->all_hosts[22],dc->all_hosts[30],10,22528,1767600.0);
	dc->instantiateFlow(dc->all_hosts[7],dc->all_hosts[22],10,630784,1771200.0);
	dc->instantiateFlow(dc->all_hosts[40],dc->all_hosts[44],10,1022976,1774800.0);
	dc->instantiateFlow(dc->all_hosts[23],dc->all_hosts[39],10,375808,1778400.0);
	dc->instantiateFlow(dc->all_hosts[26],dc->all_hosts[51],10,693248,1782000.0);
	dc->instantiateFlow(dc->all_hosts[50],dc->all_hosts[9],10,708608,1785600.0);
	dc->instantiateFlow(dc->all_hosts[20],dc->all_hosts[18],10,183296,1789200.0);
	dc->instantiateFlow(dc->all_hosts[20],dc->all_hosts[0],10,102400,1792800.0);
	dc->instantiateFlow(dc->all_hosts[28],dc->all_hosts[15],10,125952,1796400.0);


	//Main tasks that this code does is that iterate for run number of times and after every ping interval which represents 1 sec, dump the data, 

	pthread_t t1,t2;//, t3;
	pthread_create(&t1, NULL, pingFaults, NULL);

	int flowsNum = dc->all_flows.size();
	end_delay = 1000000 + 5.0;
	struct timespec time1, time2;
	time1.tv_sec = 0;
	time1.tv_nsec = 10; // interval of 100 nano sec, 

	//TODO (ali-mohsin), verify this 100 nsec is the optimal, if not then it can be optimized

	int runs = (end_delay);
	int num_fails = failTimes.size(); // would compute to 0

	cout<<"Number of run: "<<runs<<"\n";
	if(failures)
	{
		for(int i=0; i<runs; i++)
		{
			if (i%10000==0)
				cout<<i<<"th run"<<endl;
			

			dc->autofail(i);
			seconds_run++;
			if( (seconds_run % inter_ping_time) == 0 )
			{
				if( (seconds_run % 31536000) == 0 )
				{
					years_run++;
					seconds_run = seconds_run - 31536000;
				}
				long time_so_far = years_run*31536000 + seconds_run;
				dc->dumpData(time_so_far);
			}

			if(nanosleep(&time1, &time2) < 0)
			{
				cout<<"Nanosleep() failed\n";
				return -1;
			}

			for(int j=0; j<flowsNum; j++)
			{
				if( ((dc->all_flows[j]->getActive() + dc->all_flows[j]->getStart()) < run_time ) && (!(dc->all_flows[j]->getDone())))
				{
					dc->all_flows[j]->setDone(true);
					cout<<"Flow has completed!\n";
				}
			}
		}
	}
	else
	{

		cout<<"You are running simulation with out failures, You are not in Sproj 1 anymore! Please add -failure flag "<<endl;
	}

	finishThis = true;


	// ********************************** USEFUL CODE ENDS HERE *********************


	if(failures)
	{
		cout<<"fail"<<endl;
		cout<<100-(dc->downTime/(float(dc->all_flows.size())*runs))<<" Was the Availability"<<endl;
		ofstream fout;
		fout.open("failures.txt");
		string failStr = "";
		int len_cores = dc->all_cores.size();
		int len_switches = dc->all_switches.size();
		bool shouldBreak = false;

		for(int i=0; i<num_fails; i++)
		{
			if( failTimes[i] < end_delay)
			{
				shouldBreak = false;
				stringstream pI, le, dI, start, end, simTime;
				pI << failPID[i];
				le << failLevel[i];
				dI << failDID[i];
				start << failTimes[i];
				if( failComplete[i]+failTimes[i] < end_delay )
				{
					end << (failComplete[i]+failTimes[i]);
				}
				else
				{
					end << end_delay;
				}
				simTime << end_delay;

				failStr = failStr + "Failure: PodID: " + pI.str() + " Level: " + le.str() + " DeviceID: " + dI.str() + " ";
				for(int j=0; j<len_cores; j++)
				{
					if( (dc->all_cores[j]->getPodID() == failPID[i]) && (dc->all_cores[j]->getLevel() == failLevel[i]) && (dc->all_cores[j]->getDeviceID() ==failDID[i]) )
					{
						int num_up = dc->all_cores[j]->up_links.size();
						for(int l=0; l<num_up; l++)
						{
							stringstream index;
							stringstream upLink;
							index << l;
							upLink << dc->all_cores[j]->up_links[l]->getID();
							failStr = failStr + "Link: " + upLink.str() + " ";
						}
						int num_down = dc->all_cores[j]->down_links.size();
						for(int l=0; l<num_down; l++)
						{
							stringstream index;
							stringstream downLink;
							index << l;
							downLink << dc->all_cores[j]->down_links[l]->getID();
							failStr = failStr + "Link: " + downLink.str() + " ";
						}
						shouldBreak = true;
						break;
					}
				}
				if(!shouldBreak)
				{
					for(int j=0; j<len_switches; j++)
					{
						if( (dc->all_switches[j]->getPodID() == failPID[i]) && (dc->all_switches[j]->getLevel() == failLevel[i]) && (dc->all_switches[j]->getDeviceID() ==failDID[i]) )
						{
							int num_up = dc->all_switches[j]->up_links.size();
							for(int l=0; l<num_up; l++)
							{
								stringstream index;
								stringstream upLink;
								index << l;
								upLink << dc->all_switches[j]->up_links[l]->getID();
								failStr = failStr + "Link: " + upLink.str() + " ";
							}
							int num_down = dc->all_switches[j]->down_links.size();
							for(int l=0; l<num_down; l++)
							{
								stringstream index;
								stringstream downLink;
								index << l;
								downLink << dc->all_switches[j]->down_links[l]->getID();
								failStr = failStr + "Link: " + downLink.str() + " ";
							}
							shouldBreak = true;
							break;
						}
					}
				}
				failStr = failStr + "StartTime: " + start.str() + " EndTime: " + end.str() + " SimTime: " + simTime.str() + "\n";
			}
		}
		fout<<failStr;
		fout.close();
	}

	ofstream flowOut;
	flowOut.open("flows.txt");
	int num_flows = dc->all_flows.size();
	string flowStr = "";
	for(int i=0; i<num_flows; i++)
	{
		stringstream id, duration;
		id << dc->all_flows[i]->getID();
		duration << dc->all_flows[i]->getActive();
		flowStr = flowStr + " Flow: ID: " + id.str() + " Duration: " + duration.str() + "\n";
	}
	flowOut << flowStr;
	flowOut.close();

	pthread_exit(NULL);

	return 0;
}

void storeFailure(int pid, int level, int did, float fTime)
{
	failTimes.push_back(fTime);
	failPID.push_back(pid);
	failLevel.push_back(level);
	failDID.push_back(did);
	failed.push_back(false);
	failComplete.push_back(0.0);
}

void * pingFaults(void * args)
{
	struct timespec time1, time2;
	time1.tv_sec = 0;
	time1.tv_nsec = 1000000;	//this is 1 usec == 0.001 msec == 0.000001 sec
	int fault_runs = (fault_delay*1000000000)/time1.tv_nsec;	//calculating num runs to achieve the delay

	while(1)
	{
		// cout<<"here"<<endl;
		for(int i=0; i<fault_runs; i++)
		{
			if(nanosleep(&time1, &time2) < 0)
			{
				cout<<"Nanosleep() failed\n";
				exit(-1);
			}
			if(finishThis)
			{
				pthread_exit(NULL);
			}
		}
		//call the detect fault function

		// while(busy)
		// {
		// 	if(nanosleep(&time1, &time2) < 0)
		// 	{
		// 		cout<<"Nanosleep() failed\n";
		// 		exit(-1);
		// 	}
		// }
		// busy = true;
		run_faults = run_time;
//		cout<<"About to find faults!\n";
		dc->findFaults();
//		cout<<"Done finding faults!\n";
		// busy = false;

		if(finishThis)
		{
			pthread_exit(NULL);
		}
	}

}
import java.io.*;
import java.util.*;

public class H {

    private static int testcases, n, b, c;
    private static int currentTestcase = 1;
    private static BufferedReader in;
    private static String currentLine;
    private static int[] A;
    private static int[] numberOfElements;
    private static boolean[] married;
    private static Map<Integer, Set<Integer>> representatives;
    private static List<Time> possibleTimes;
    private static Map<Integer, Set<Integer>> lights;



    public static void main(String[] args) throws FileNotFoundException {
        in = new BufferedReader(new InputStreamReader(getInputStream()));

        try {
            currentLine = in.readLine();
            testcases = Integer.parseInt(currentLine);
            while (currentTestcase <= testcases) {
                doStuff();
                currentTestcase++;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void doStuff() throws IOException {
        currentLine = in.readLine();
        String[] input = currentLine.split(" ");
        n = Integer.parseInt(input[0]);

        List<Time> observedTimes = new LinkedList<>();

        representatives = new HashMap<>();
        Set<Integer> zeroRepresents = new HashSet<>();
        zeroRepresents.add(0);
        zeroRepresents.add(8);
        representatives.putIfAbsent(0, zeroRepresents);
        Set<Integer> oneRepresents = new HashSet<>();
        oneRepresents.add(0);
        oneRepresents.add(1);
        oneRepresents.add(3);
        oneRepresents.add(4);
        oneRepresents.add(7);
        oneRepresents.add(8);
        oneRepresents.add(9);
        representatives.putIfAbsent(1, oneRepresents);
        Set<Integer> twoRepresents = new HashSet<>();
        twoRepresents.add(2);
        twoRepresents.add(8);
        representatives.putIfAbsent(2, twoRepresents);
        Set<Integer> threeRepresents = new HashSet<>();
        threeRepresents.add(3);
        threeRepresents.add(8);
        threeRepresents.add(9);
        representatives.putIfAbsent(3, threeRepresents);
        Set<Integer> fourRepresents = new HashSet<>();
        fourRepresents.add(4);
        fourRepresents.add(8);
        fourRepresents.add(9);
        representatives.putIfAbsent(4, fourRepresents);
        Set<Integer> fiveRepresents = new HashSet<>();
        fiveRepresents.add(5);
        fiveRepresents.add(6);
        fiveRepresents.add(8);
        fiveRepresents.add(9);
        representatives.putIfAbsent(5, fiveRepresents);
        Set<Integer> sixRepresents = new HashSet<>();
        sixRepresents.add(6);
        sixRepresents.add(8);
        representatives.putIfAbsent(6, sixRepresents);
        Set<Integer> sevenRepresents = new HashSet<>();
        sevenRepresents.add(3);
        sevenRepresents.add(7);
        sevenRepresents.add(8);
        sevenRepresents.add(9);
        sevenRepresents.add(0);
        representatives.putIfAbsent(7, sevenRepresents);
        Set<Integer> eightRepresents = new HashSet<>();
        eightRepresents.add(8);
        representatives.putIfAbsent(8, eightRepresents);
        Set<Integer> nineRepresents = new HashSet<>();
        nineRepresents.add(8);
        nineRepresents.add(9);
        representatives.putIfAbsent(9, nineRepresents);
        
        //add lights that are on for a number - to visualize it, use an eight and draw a backwards "S" on top of it. Index starts at 1 with the upper square on the left
        lights = new HashMap<>();
        lights.putIfAbsent(0, new HashSet<>(Arrays.asList(1,2,3,5,6,7)));
        lights.putIfAbsent(1, new HashSet<>(Arrays.asList(3,7)));
        lights.putIfAbsent(2, new HashSet<>(Arrays.asList(2,3,4,5,6)));
        lights.putIfAbsent(3, new HashSet<>(Arrays.asList(2,3,4,6,7)));
        lights.putIfAbsent(4, new HashSet<>(Arrays.asList(1,3,4,7)));
        lights.putIfAbsent(5, new HashSet<>(Arrays.asList(1,2,4,6,7)));
        lights.putIfAbsent(6, new HashSet<>(Arrays.asList(1,2,4,5,6,7)));
        lights.putIfAbsent(7, new HashSet<>(Arrays.asList(2,3,7)));
        lights.putIfAbsent(8, new HashSet<>(Arrays.asList(1,2,3,4,5,6,7)));
        lights.putIfAbsent(9, new HashSet<>(Arrays.asList(1,2,3,4,6,7)));

        for (int i = 0; i < n; i++) {
            input = in.readLine().split(":");
            int hours = Integer.parseInt(input[0]);
            int minutes = Integer.parseInt(input[1]);
            Time time = new Time(hours / 10, hours % 10, minutes / 10, minutes % 10);
            observedTimes.add(time);
        }

        possibleTimes = new ArrayList<>();
        calculateInitialPossibleTimes(observedTimes.get(0));

        for(int i = 1; i < n; i++){
            updatePossibleTimes(observedTimes.get(i), i);
        }

        /*
            addendum: based on the result, filter out those times which are not possible due to the light 
            not working in previous times
        */
        filterResult(observedTimes);


        System.out.format("Case #%d:\n%s", currentTestcase, printResult());
        in.readLine();
    }

    private static String printResult() {
        StringBuilder sb = new StringBuilder();

        if(possibleTimes.isEmpty()){
            return "none\n";
        }

        for(Time time : possibleTimes){
            sb.append(time.hourTens).append(time.hourOnes).append(":").append(time.minuteTens).append(time.minuteOnes).append("\n");
        }

        return sb.toString();
    }

    private static void filterResult(List<Time> observedTimes){
    	
    	Set<Integer> offHours1;
    	Set<Integer> offHours2;
    	Set<Integer> offMin1;
    	Set<Integer> offMin2;
    	
    	Set<Time> removeIndex = new HashSet<Time>();
    	
    	for (Time t : possibleTimes){
    		int count = 0;
    		for(Time ob : observedTimes){
    			Set<Integer> tmp;
    			Time current = new Time(t);
    			current.addMin(count);
    			//hourTens
    			tmp = new HashSet<Integer>(lights.get(current.hourTens));
    			tmp.removeAll(lights.get(ob.hourTens));
    			offHours1 = tmp;
    			if(checkOff(offHours1,observedTimes,1)){
    				removeIndex.add(t);
    				break;
    			}
    			
    			//hourOnes
    			tmp = new HashSet<Integer>(lights.get(current.hourOnes));
    			tmp.removeAll(lights.get(ob.hourOnes));
    			offHours2 = tmp;
    			if(checkOff(offHours2,observedTimes,2)){
    				removeIndex.add(t);
    				break;
    			}
    			
    			//minuteTens
    			tmp = new HashSet<Integer>(lights.get(current.minuteTens));
    			tmp.removeAll(lights.get(ob.minuteTens));
    			offMin1 = tmp;
    			if(checkOff(offMin1,observedTimes,3)){
    				removeIndex.add(t);
    				break;
    			}
    			
    			//minuteOnes
    			tmp = new HashSet<Integer>(lights.get(current.minuteOnes));
    			tmp.removeAll(lights.get(ob.minuteOnes));
    			offMin2 = tmp;
    			if(checkOff(offMin2,observedTimes,4)){
    				removeIndex.add(t);
    				break;
    			}
    			count++;
    			
    		}

    	}
    	
    	for (Time t : removeIndex){
    		possibleTimes.remove(t);
    	}
    	
    }
    
    //digit here means the position on the clock from 1-4
    private static boolean checkOff(Set<Integer> off, List<Time> observedTimes, int digit){
    	
    	for(Integer broken : off){
    		for(Time o : observedTimes){
    			switch (digit) {
				case 1:
					if (lights.get(o.hourTens).contains(broken))
						return true;
					break;
				case 2:
					if (lights.get(o.hourOnes).contains(broken))
						return true;
					break;
				case 3:
					if (lights.get(o.minuteTens).contains(broken))
						return true;
					break;
				case 4:
					if (lights.get(o.minuteOnes).contains(broken))
						return true;
					break;
				default:
					break;
				}
    			
    		}
    	}
    	return false;
    }
    
    private static void updatePossibleTimes(Time observedTime, int minutesSinceStart) {
        Set<Integer> indicesToBeRemoved = new HashSet<>();
        for(int i = possibleTimes.size() - 1; i >= 0; i--){
            Time possibleTime = possibleTimes.get(i);
            int possibleTimeMinutes = 10 * possibleTime.minuteTens + possibleTime.minuteOnes;
            int targetMinutes = (possibleTimeMinutes + minutesSinceStart) % 60;
            int targetMinuteTens = targetMinutes / 10;
            int targetMinuteOnes = targetMinutes % 10;
            int targetHours = possibleTimeMinutes + minutesSinceStart < 60 ? 10 * possibleTime.hourTens + possibleTime.hourOnes : (10 * possibleTime.hourTens + possibleTime.hourOnes + 1) % 24;
            int targetHourTens = targetHours / 10;
            int targetHourOnes = targetHours % 10;

            if(!representatives.get(observedTime.hourTens).contains(targetHourTens) ||
                    !representatives.get(observedTime.hourOnes).contains(targetHourOnes) ||
                    !representatives.get(observedTime.minuteTens).contains(targetMinuteTens) ||
                    !representatives.get(observedTime.minuteOnes).contains(targetMinuteOnes)) {

                possibleTimes.remove(i);
            }
        }
    }

    private static void calculateInitialPossibleTimes(Time observedTime) {
        for(Integer hourTens : representatives.get(observedTime.hourTens)){
            if (hourTens > 2){
                continue;
            } else if(hourTens == 2){
                for(Integer hourOnes : representatives.get(observedTime.hourOnes)) {
                    if(hourOnes > 3){
                        continue;
                    } else {
                        for (Integer minuteTens : representatives.get(observedTime.minuteTens)) {
                            if (minuteTens > 5) {
                                continue;
                            } else {
                                for (Integer minutesOnes : representatives.get(observedTime.minuteOnes)) {
                                    possibleTimes.add(new Time(hourTens, hourOnes, minuteTens, minutesOnes));
                                }
                            }
                        }
                    }
                }

            } else {
                for(Integer hourOnes : representatives.get(observedTime.hourOnes)) {
                    for(Integer minuteTens : representatives.get(observedTime.minuteTens)){
                        if (minuteTens > 5){
                            continue;
                        } else {
                            for (Integer minutesOnes : representatives.get(observedTime.minuteOnes)) {
                                possibleTimes.add(new Time(hourTens, hourOnes, minuteTens, minutesOnes));
                            }
                        }
                    }
                }
            }
        }
    }

    private static class Time{
        public int hourTens, hourOnes, minuteTens, minuteOnes;

        public Time(int hourTens, int hourOnes, int minuteTens, int minuteOnes) {
            this.hourTens = hourTens;
            this.hourOnes = hourOnes;
            this.minuteTens = minuteTens;
            this.minuteOnes = minuteOnes;
        }
        public Time(Time t){
        	this.hourTens = t.hourTens;
        	this.hourOnes = t.hourOnes;
        	this.minuteOnes = t.minuteOnes;
        	this.minuteTens = t.minuteTens;
        }
        
        public void addMin(int i){
        	minuteOnes += i;
        	if(minuteOnes > 9){
        		int over = minuteOnes/10;
        		minuteOnes -= 10 * over;
        		minuteTens += over;
        		if (minuteTens > 5){
        			over = minuteTens/6;
        			minuteTens -= 6*over;
        			hourOnes += over;
        			if ( (hourTens == 2 && hourOnes > 3) || hourOnes > 9){
        				if (hourTens == 2){
        					over = hourOnes/4;
        					hourOnes -= 4 * over;
        				} else {
        					over = hourOnes/10;
        					hourOnes -= 10 * over;
        					}
        				hourTens += over;
        				if(hourTens > 2){
        					//not enough but should work for our case
        					hourTens = 0; hourOnes = 0;
        				}
        			}
        		}
        	}
        }
    }

    private static InputStream getInputStream() throws FileNotFoundException {
        //return new FileInputStream("src/week11/ex8/input.txt");
        return System.in;
    }

}